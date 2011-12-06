#include "read.h"

/* Cette tache consiste à  traiter les messages reçu par le client */

// a supprimer
int sock;

//provisoire, à supprimer
	MSG_Q_ID msgQId;

void handlingMessage(char* replyBuf){
	int type;
	type = (int)replyBuf[0];
	switch(type){
	case 'i': // On rajoute un message dans la boite aux lettres lots
		//msgQSend(msg);
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

// a enlever car ce code se trouve dans la tache mère
int createsocket()
{
	struct sockaddr_in serverAddr;
		struct sockaddr_in clientAddr;
		struct request myRequest;

		// creation d'une socket (SOCK_STREAM pour protocole TCP)
		int s = socket(AF_INET, SOCK_STREAM, 0);
		// Assign address to socket

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
		// Complete connection between sockets
		accept(s, (struct sockaddr *) &clientAddr, &sockAddrSize);
		sock = s;
}

// Fin du à enlever

void client(){
	
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
