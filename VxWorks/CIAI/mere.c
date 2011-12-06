/*#include <vxworks.h>*/
#include <taskLib.h> 	/* Gestion des taches    */
#include <semLib.h>  	/* Gestion des semaphores*/
#include <wdLib.h>	    /* Gestion des alarmes   */
/* GESTION RESEAU */
#include <sockLib.h>
#include <inetLib.h>
#include <strLib.h>
/* GESTION FICHIER */
#include <string.h>
/* GESTION TACHES */
#include "mere.h"		/* Interface			 */
#include "boxing.h"		/* Interface de la tache Conditionnement */
#include "packaging.h" 	/* Interface de la tache Mise en palette */
#include "warehouse.h"	/* Interface de la tache Gestion entrepot*/
#include "read.h"	 	/* Interface de la tache Lire			 */
#include "writefile.h"  /* Interface de la tache Ecrire			 */
#include "writesocket.h"/* Interface de la tache Ecrire			 */

static void initialisation()
{
	tid_main = taskIdSelf();
	taskPrioritySet(tid_main, 10); 	/* Redefinition de la priorite */
	
	/* CREATION DU FICHIER */
    message_file = fopen("messages","w");

	/* INITIALISATION DES VARIABLES */

	/* INITIALISATION DE LA SOCKET */
	createsocket();

	/*Creation des BAL*/
	mid_boxing_todo   = msgQCreate(10,4,0); //Create a msg queue with 10 msg max,
											//4 byte per msg max, and msgs filled up in fifo order
	mid_boxing_done   = msgQCreate(10,4,0); //Create a msg queue with 10 msg max,
											//4 byte per msg max, and msgs filled up in fifo order
	mid_received_part = msgQCreate(10,4,0); //Create a msg queue with 10 msg max,
												//4 byte per msg max, and msgs filled up in fifo order
	mid_log			  = msgQCreate(10,4,0); //Create a msg queue with 10 msg max,
											//4 byte per msg max, and msgs filled up in fifo order
	mid_packaging  	  = msgQCreate(10,4,0); //Create a msg queue with 10 msg max,
											//4 byte per msg max, and msgs filled up in fifo order
	mid_batch 	 	  = msgQCreate(10,4,0); //Create a msg queue with 10 msg max,
											//4 byte per msg max, and msgs filled up in fifo order
	mid_boxing   	  = msgQCreate(10,4,0); //Create a msg queue with 10 msg max,
											//4 byte per msg max, and msgs filled up in fifo order							
	
	/*Creation des taches*/
	tid_boxing         = taskSpawn("boxing",     					 /* name of new task (stored at pStackBase) */
							  20,                                    /* priority of new task */
							  0x0008,                                /* task option word */
							  10000,                                 /* size (bytes) of stack needed plus name */
							  (FUNCPTR) startBoxing,		         /* entry point of new task */
							  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
							  );
	tid_packaging      = taskSpawn("packaging",     				 /* name of new task (stored at pStackBase) */
							  25,                                    /* priority of new task */
							  0x0008,                                /* task option word */
							  10000,                                 /* size (bytes) of stack needed plus name */
							  (FUNCPTR) startPackaging,		         /* entry point of new task */
							  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
							  );
	tid_warehouse      = taskSpawn("warehouse",     			     /* name of new task (stored at pStackBase) */
							  30,                                    /* priority of new task */
							  0x0008,                                /* task option word */
							  10000,                                 /* size (bytes) of stack needed plus name */
							  (FUNCPTR) startWarehouse,		         /* entry point of new task */
							  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
							  );
	tid_writefile      = taskSpawn("writefile",     				 /* name of new task (stored at pStackBase) */
							  40,                                    /* priority of new task */
							  0x0008,                                /* task option word */
							  10000,                                 /* size (bytes) of stack needed plus name */
							  (FUNCPTR) startWriteFile,		         /* entry point of new task */
							  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
							  );
	tid_writesocket    = taskSpawn("writesocket",     				 /* name of new task (stored at pStackBase) */
							  40,                                    /* priority of new task */
							  0x0008,                                /* task option word */
							  10000,                                 /* size (bytes) of stack needed plus name */
							  (FUNCPTR) startWriteSocket,		     /* entry point of new task */
							  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
							  );
	tid_read           = taskSpawn("read",     						 /* name of new task (stored at pStackBase) */
							  40,                                    /* priority of new task */
							  0x0008,                                /* task option word */
							  10000,                                 /* size (bytes) of stack needed plus name */
							  (FUNCPTR) startRead,		             /* entry point of new task */
							  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
							  );
}

static void destruction()
{
	/* Fermeture du fichier */
	fclose(message_file);
	/* TO DO */
	printf("Fin de tache\n");
	exit(0); /*auto-destruction*/
}

int main(int argc, char * argv[])
{
	initialisation();
	taskSuspend(0);
	//moteur();
	destruction();
	return 0;
}

static int createsocket()
{
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	struct request myRequest;
	int sockAddrSize;
	// creation d'une socket (SOCK_STREAM pour protocole TCP)
	sock = socket(AF_INET, SOCK_STREAM, 0);
	// Assign address to socket
	sockAddrSize = sizeof (struct sockaddr_in);
	bzero ((char *) &serverAddr, sockAddrSize);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_len = (u_char) sockAddrSize;
	serverAddr.sin_port = htons (SERVER_PORT_NUM);
	serverAddr.sin_addr.s_addr = htonl (INADDR_ANY);
	printf("Hello Hicham3\n");
	bind(sock, (struct sockaddr  *) &serverAddr, sockAddrSize);

	// Allow others to connect to socket
	listen(sock, 1);
	// Complete connection between sockets
	accept(sock, (struct sockaddr *) &clientAddr, &sockAddrSize);
}
