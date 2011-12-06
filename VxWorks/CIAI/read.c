#include "read.h"

/* Cette tache consiste à  traiter les messages reçu par le client */

void handlingMessage(char* replyBuf){
	int type;
	type = (int)replyBuf[0];
	switch(type){
	case 'i': 
		// On rajoute un message dans la boite aux lettres lots = mid_packaging
		msgQSend(mid_packaging, replyBuf, strlen(replyBuf), NO_WAIT, MSG_PRI_NORMAL);
		break;
	case 'c':
		// On rajoute un message dans la boite aux lettres palettes finis = mid_boxing_done
		msgQSend(mid_boxing_done, replyBuf, strlen(replyBuf), NO_WAIT, MSG_PRI_NORMAL);
		break;
	case 'a':
		// TODO
		break;
	}	
} // handlingMessage()

void startRead(){
	
	char * replyBuf;	
	// Lire le contenu de la socket
//	for(ioctl (sFd, FIONREAD,&byteAvailebal); ;ioctl (sFd, FIONREAD,&byteAvailebal))
//	{
//		if(0 == byteAvailebal)
//			continue;
		read(sock, replyBuf, 0);
		handlingMessage(replyBuf);
//	}
}
