#include <sockLib.h>
#include <strLib.h>
#include <taskLib.h>
#include "mere.h"
#include "defs.h"
#include "usine.h"


void startRead(){	
	char type;	
	int nbPack1;
	int nbPack2;
	message answer;
	int batchNumber=0;
	int commandNumber=0;
	batch toDo;
	pack toGet;
	for (;;)
	{	
		//First read the message type :
		read(sock, &type, sizeof(char));
		switch(type){
		case 'a':
#ifdef test
			printf("reveived a start/stop command");
#endif
			//answer
			read(sock,answer,sizeof(char));//get answer type
			//send it to mere.
			if (answer[0]=='s')
			{
    			sprintf(answer+1,"Terminating application");
			}else{
				sprintf(answer+1,"Restarting application");
			}
			msgQSend(mid_actions,answer,sizeof(message),WAIT_FOREVER,MSG_PRI_URGENT);
			break;
		case 'i':
			//Init
#ifdef test
			printf("reveived an init command");
#endif
			read(sock,(char*)&nbPack1,sizeof(int));
			read(sock,(char*)&nbPack2,sizeof(int));
			toDo.batchNumber=batchNumber++;
			toDo.nbPack1=nbPack1;
			toDo.nbPack2=nbPack2;
			msgQSend(mid_batch,(char*)&toDo,sizeof(toDo),WAIT_FOREVER,MSG_PRI_NORMAL);
			break;
		case 'c':
			//command
#ifdef test
			printf("reveived an order command");
#endif
			read(sock,(char*)&nbPack1,sizeof(int));
			read(sock,(char*)&nbPack2,sizeof(int));
			toGet.number=commandNumber++;
			toGet.size=0;
			toGet.nbType1=-1*nbPack1;
			toGet.nbType2=-1*nbPack2;
			msgQSend(mid_packaging,(char*)&toDo,sizeof(toDo),WAIT_FOREVER,MSG_PRI_URGENT);
			//Message urgent because we don't want to wait for all the incomming 
			//packs to be handled by the warehouse before they handle incomming orders
			break;
		}
	}
}
