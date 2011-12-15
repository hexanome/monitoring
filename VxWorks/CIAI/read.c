/**
 * tâche conste à recevoir et à traiter les commandes reçu par le superviseur
 */

#include "read.h"


/**
 * traitement des commandes reçus
 */
void handlingMessage(char* replyBuf){
	char type;
	type =)replyBuf[0];
	switch(type){
	case 'i': 
		// On rajoute un message dans la boite aux lettres lots = mid_packaging
		msgQSend(mid_batch, replyBuf, strlen(replyBuf), NO_WAIT, MSG_PRI_NORMAL);
		break;
	case 'c':
		// On rajoute un message dans la boite aux lettres palettes finis = mid_boxing_done
		msgQSend(mid_boxing_done, replyBuf, strlen(replyBuf), NO_WAIT, MSG_PRI_NORMAL);
		break;
	case 'a':
		// On inscrit la r�ponse dans le s�maphore M
		// TODO
		// On r�active la tache m�re
		taskResume(tid_main);
		break;
	}	
} // handlingMessage()

/**
 * reçoit les commandes envoyer par le superviseur et faire appele à la fonction de traitement
 */
void startRead(){	
	for (;;)
	{	
		char * replyBuf;		
		//for(ioctl (sFd, FIONREAD,&byteAvailebal); ;ioctl (sFd, FIONREAD,&byteAvailebal))
		//{
		//if(0 == byteAvailebal)
		//continue;
		// Lire le contenu de la socket
		read(sock, replyBuf, 0);
		handlingMessage(replyBuf);
		//	}
	}
}
