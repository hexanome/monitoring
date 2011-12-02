/*#include <vxworks.h>*/
#include <taskLib.h> 	/* Gestion des taches    */
#include <semLib.h>  	/* Gestion des semaphores*/
#include <wdLib.h>	    /* Gestion des alarmes   */
#include "mere.h"		/* Interface			 */
#include "boxing.h"		/* Interface de la tache Conditionnement */
#include "packaging.h" 	/* Interface de la tache Mise en palette */
#include "warehouse.h"	/* Interface de la tache Gestion entrepot*/
#include "read.h"	 	/* Interface de la tache Lire			 */
#include "write.h"	 	/* Interface de la tache Ecire			 */

void initialisation()
{
	tid_main = taskIdSelf();
	/*Redefinition de la priorite*/
	taskPrioritySet(tid_main, 10);
	/*Redefinition de l'horloge
	sysClkRateSet(100); /*Plus simple pour avoir un dixieme de seconde*/

	/*INITIALISATION DES VARIABLES */
	

	/*Creation des semaphores binaires pour les ressources critiques*/
	semResponse = semMCreate(SEM_Q_FIFO, SEM_FULL);					 /*Semaphore de la communication avec le robot*/

	/* INITIALISATION DE LA SOCKET */

	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;

	// Inutile pour l'instant, à voir si c'est util
	struct request
	{
	    int reply; /* TRUE = request reply from
	    server */
	    int msgLen; /* length of message text */
	    char message[5]; /* message buffer */
	};

	struct request myRequest;

	// création d'une socket (SOCK_STREAM pour protocole TCP)
	int s = socket(AF_INET, SOCK_STREAM, 0);
	//Assign address to socket

	int sockAddrSize = sizeof (struct sockaddr_in);
	bzero ((char *) &serverAddr, sockAddrSize);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_len = (u_char) sockAddrSize;
	serverAddr.sin_port = htons (SERVER_PORT_NUM);
	serverAddr.sin_addr.s_addr = htonl (INADDR_ANY);
	printf("Hello Hicham3\n");
	bind(s, (struct sockaddr  *) &serverAddr, sockAddrSize);

	// Allow others to connect to socket
	listen(s, 1);
	
	/*Creation des taches*/
	tid_boxing     = taskSpawn("boxing",     						 /* name of new task (stored at pStackBase) */
							  20,                                    /* priority of new task */
							  0x0008,                                /* task option word */
							  10000,                                 /* size (bytes) of stack needed plus name */
							  (FUNCPTR) menu,		         		 /* entry point of new task */
							  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
							  );
	tid_packing    = taskSpawn("packing",     						 /* name of new task (stored at pStackBase) */
							  25,                                    /* priority of new task */
							  0x0008,                                /* task option word */
							  10000,                                 /* size (bytes) of stack needed plus name */
							  (FUNCPTR) deplacer,		             /* entry point of new task */
							  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
							  );
	tid_warehouse  = taskSpawn("warehouse",     					 /* name of new task (stored at pStackBase) */
							  30,                                    /* priority of new task */
							  0x0008,                                /* task option word */
							  10000,                                 /* size (bytes) of stack needed plus name */
							  (FUNCPTR) capteur,		             /* entry point of new task */
							  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
							  );
	tid_write      = taskSpawn("write",     						 /* name of new task (stored at pStackBase) */
							  40,                                    /* priority of new task */
							  0x0008,                                /* task option word */
							  10000,                                 /* size (bytes) of stack needed plus name */
							  (FUNCPTR) capteur,		             /* entry point of new task */
							  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
							  );
	tid_read       = taskSpawn("read",     						     /* name of new task (stored at pStackBase) */
							  40,                                    /* priority of new task */
							  0x0008,                                /* task option word */
							  10000,                                 /* size (bytes) of stack needed plus name */
							  (FUNCPTR) capteur,		             /* entry point of new task */
							  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
							  );
	/*Creation de l'alarme*/
	alarme = wdCreate();
	wdStart(alarme, sysClkRateGet(), (FUNCPTR) temporisation, 0); /*toutes les secondes !*/

	/*Allumer la led 0 (mode automatique)*/
	semTake(semCommande, WAIT_FOREVER); /*Prendre un jeton (attente bloquante et permanente)*/
	write("L,0,1\r", instring);   		/*led 0 allume*/
	write("L,1,0\r", instring);   		/*led 1 eteinte*/
	semGive(semCommande);               /*Rendre un jeton*/
	}
}

void destruction()
{
	/*Destruction de l'alarme*/
	wdDelete(alarme);
	
	/*Destruction des taches*/
	printf("Destruction des taches restantes\n");
	taskSuspend(tid_capteur);
	taskDelete(tid_capteur);
	taskSuspend(tid_deplacer);
	taskDelete(tid_deplacer);
	taskSuspend(tid_menu);
	taskDelete(tid_menu);
	
	/*Destruction des semaphores*/
	printf("Destruction des semaphores\n");
	semDelete(semCommunication);
	semDelete(semMode);
	semDelete(semObstacle);
	semDelete(semCommande);
	
	/*DONC ON N'EST PLUS QUE LE SEUL A COMMUNIQUER AVEC LE KHEPERA
	AINSI PAS UTILITE DE BLINDER AVEC L'UTILISATION
	DU SEMAPHORE DE COMMUNICATION
	Arret des moteurs*/
	ecrire("D,0,0\r", instring);
	
	/*Extinction des led*/
	ecrire("L,0,0\r", instring); /*led 0*/
	ecrire("L,1,0\r", instring); /*led 1*/
	
	/*Destruction des variables*/
	
	/*Fin de la connexion
	printf("Deconnexion en cours");
	printf(close_85230());*/

	/*Nettoyage ecran*/
	nettoyage_ecran();

	/*Fin de la tache*/
	printf("Fin de tache\n");
	exit(0); /*auto-destruction*/
}

int main()
{
	initialisation();
	taskSuspend(0);
	moteur();
	destruction();
	return 0;
}