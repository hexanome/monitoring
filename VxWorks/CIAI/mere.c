/*#include <vxworks.h>*/
#include <taskLib.h> 	/* Gestion des taches    */
#include <semLib.h>  	/* Gestion des semaphores*/
#include <wdLib.h>	/* Gestion des alarmes   */
/* GESTION RESEAU */
#include <sockLib.h>
#include <inetLib.h>
#include <strLib.h>
/* GESTION FICHIER */
#include <string.h>
/* GESTION TACHES */
#include "mere.h"	/* Interface de mere */
#include "tasks.h"	/* Interface de la tache Conditionnement */
#include "usine.h"
#include "defs.h"

static int stopped=0;
static void destruction();
static void initialisation()
{
	tid_main = taskIdSelf();
	taskPrioritySet(tid_main, 10); 	/* Redefinition de la priorite */	

	/* CREATION DU FICHIER */
    	message_file = fopen("messages","w");

	/* INITIALISATION DES VARIABLES */

	/* INITIALISATION DE LA SOCKET */
	createsocket();	

	/* Creation du semaphore */
	sid_recover = semMCreate(SEM_Q_FIFO);

	/* Creation des BAL*/
	mid_boxing_todo		= msgQCreate(10,4,0); //Create a msg queue with 10 msg max,
											//4 byte per msg max, and msgs filled up in fifo order
	mid_boxing_done		= msgQCreate(10,4,0); //Create a msg queue with 10 msg max,
											//4 byte per msg max, and msgs filled up in fifo order
	mid_received_part	= msgQCreate(10,4,0); //Create a msg queue with 10 msg max,
												//4 byte per msg max, and msgs filled up in fifo order
	mid_log			= msgQCreate(10,4,0); //Create a msg queue with 10 msg max,
											//4 byte per msg max, and msgs filled up in fifo order
	mid_log_file		= msgQCreate(10,4,0); //Create a msg queue with 10 msg max,
											//4 byte per msg max, and msgs filled up in fifo order
	mid_packaging		= msgQCreate(10,4,0); //Create a msg queue with 10 msg max,
											//4 byte per msg max, and msgs filled up in fifo order
	mid_batch		= msgQCreate(10,4,0); //Create a msg queue with 10 msg max,
	mid_actions		= msgQCreate(10,4,0); //Create a msg queue with 10 msg max,	

	/*Creation des taches*/
	tid_boxing         = taskSpawn("boxing",					/* name of new task (stored at pStackBase) */
							  20,				/* priority of new task */
							  0,				/* task option word */
							  10000,			/* size (bytes) of stack needed plus name */
							  (FUNCPTR) startBoxing,	/* entry point of new task */
							  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
							  );
	tid_packaging      = taskSpawn("packaging",					/* name of new task (stored at pStackBase) */
							  25,				/* priority of new task */
							  0,				/* task option word */
							  10000,			/* size (bytes) of stack needed plus name */
							  (FUNCPTR) startPackaging,	/* entry point of new task */
							  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
							  );
	tid_warehouse      = taskSpawn("warehouse",     			     	/* name of new task (stored at pStackBase) */
							  30,				/* priority of new task */
							  0,				/* task option word */
							  10000,			/* size (bytes) of stack needed plus name */
							  (FUNCPTR) startWarehouse,	/* entry point of new task */
							  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
							  );
	tid_writefile      = taskSpawn("writefile",					/* name of new task (stored at pStackBase) */
							  40,				/* priority of new task */
							  0,				/* task option word */
							  10000,			/* size (bytes) of stack needed plus name */
							  (FUNCPTR) startWriteFile,	/* entry point of new task */
							  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
							  );
	tid_writesocket    = taskSpawn("writesocket",					/* name of new task (stored at pStackBase) */
							  40,				/* priority of new task */
							  0,				/* task option word */
							  10000,			/* size (bytes) of stack needed plus name */
							  (FUNCPTR) startWriteSocket,	/* entry point of new task */
							  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
							  );
	tid_read           = taskSpawn("read",						/* name of new task (stored at pStackBase) */
							  40,				/* priority of new task */
							  0,				/* task option word */
							  10000,			/* size (bytes) of stack needed plus name */
							  (FUNCPTR) startRead,		/* entry point of new task */
							  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
							  );
}

static void moteur(){
	message buff;
	msgQReceive(mid_actions,buff,sizeof(buff),WAIT_FOREVER);
	//log error : 
	msgQSend(mid_log,buff,sizeof(message),NO_WAIT,MSG_PRI_URGENT);
	switch (buff[0]){
	case 'p':
		//error in packaging, let's stop boxing and packaging :
		closeTrap();
		taskSuspend(tid_packaging);
		taskSuspend(tid_boxing);
		stopped=1;
		break;
	case 'b':
		//error in boxing, let's stop it :
		closeTrap();
		taskSuspend(tid_boxing);
		stopped=1;
		break;
	case 'c':
		//test if we're stoped, and if we are, start.
		if (stopped==0){break;}
		taskResume(tid_packaging);
		taskResume(tid_boxing);
		stopped=0;
		openTrap();
		break;
	case 's':
		//test if we're stopped, and if we are terminate app.
		if (stopped==0){break;}
		return;
		break;
	}
}

static void destruction()
{
	/* Fermeture du fichier */
	closeTrap();
	taskDelete(tid_boxing);
	taskDelete(tid_packaging);
	taskDelete(tid_read);
	taskDelete(tid_warehouse);
	taskDelete(tid_writefile);
	taskDelete(tid_writesocket);
	semDelete(sid_recover);
	msgQDelete(mid_actions);
	msgQDelete(mid_batch);
	msgQDelete(mid_boxing_done);
	msgQDelete(mid_boxing_todo);
	msgQDelete(mid_log);
	msgQDelete(mid_log_file);
	msgQDelete(mid_packaging);
	msgQDelete(mid_received_part);
	fclose(message_file);
	close(sock);
#ifdef test
	printf("Fin de tache\n");
#endif
	exit(0); /*auto-destruction*/
}

int main(int argc, char * argv[])
{
	initialisation();
	moteur();
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
	bind(sock, (struct sockaddr  *) &serverAddr, sockAddrSize);

	// Allow others to connect to socket
	listen(sock, 1);

	// Complete connection between sockets
	accept(sock, (struct sockaddr *) &clientAddr, &sockAddrSize);
}

//This two functions won't be used by mere, instead they will be used by all taks
//that need to send errors and messages to mere
void error(char * messageText, char sender){
	message message;
	memcpy(message+1,messageText,sizeof(messageText)-1);
	message[0]=sender;
	closeTrap();
	msgQSend(mid_actions,message,sizeof(message),NO_WAIT,MSG_PRI_NORMAL);
}

void info(char * messageText){
	message message;
	memcpy(message+1,messageText,sizeof(messageText)-1);
	message[0]=' ';
	msgQSend(mid_log,message,sizeof(message),NO_WAIT,MSG_PRI_NORMAL);
}