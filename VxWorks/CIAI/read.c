#include "stdio.h"
#include "sockLib.h"

// faire du tri dans les includes inutiles
#include "vxWorks.h"
#include "inetLib.h"
#include "stdioLib.h"
#include "strLib.h"
#include "hostLib.h"

#define SERVER_PORT_NUM 5001
#define REPLY_MSG_SIZE 100 // provisoir

/**
 * cette fonction consiste à traiter les messages reçu par le client
 * 
 */
void handlingMessage(char* replyBuf){
	int type;
	type = (int)replyBuf[0];
	switch(type){
	case 'i':
		// TODO
		break;
	case 'c':
		// TODO
		break;
	case 'a':
		// TODO
		break;
	}
	
} // handlingMessage()

/**
 * 
 */
void client(){
	// creation
	struct sockaddr_in clientAddr;
	int clientAddrSize = sizeof (struct sockaddr_in);
	int s, byteAvailebal;
	char replyBuf[REPLY_MSG_SIZE];
	
	//initialisation des paramètre de l'adresse
	bzero ((char *) &clientAddr, clientAddrSize);
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_len = (u_char) clientAddrSize;
	clientAddr.sin_port = htons (SERVER_PORT_NUM);
	clientAddr.sin_addr.s_addr = htonl (INADDR_ANY);
	
	// initialistion de la socket
	s = socket(AF_INET, SOCK_STREAM, 0);
	
	// connecter la socket avec l'adresse du client
	connect(s,(struct sockaddr  *) &clientAddr,clientAddrSize);
	
	//lire le contenue de la socket
	for(ioctl (sFd, FIONREAD,&byteAvailebal); ;ioctl (sFd, FIONREAD,&byteAvailebal))
	{
		if(0 == byteAvailebal)
			continue;
		read(s, replyBuf, REPLY_MSG_SIZE);
		handlingMessage(replyBuf);
	}
}
