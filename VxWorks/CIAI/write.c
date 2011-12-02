#include "stdio.h"
#include "sockLib.h"

// faire du tri dans les includes inutiles
#include "vxWorks.h"
#include "inetLib.h"
#include "stdioLib.h"
#include "strLib.h"
#include "hostLib.h"
//#include "ioLib.h"


#define SERVER_PORT_NUM 5001

void writes()
{
	
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	
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

	// Complete connection between sockets
	accept(s, (struct sockaddr *) &clientAddr, &sockAddrSize);

	myRequest.msgLen = 5;
	myRequest.message[1] = 'c';
	myRequest.message[2] = 'o';
	myRequest.message[3] = 'u';
	myRequest.message[4] = 'c';
	myRequest.message[5] = 'o';
	
	// Boucle infini de la tache
	for (;;)
	{
		//On attend un message de la boite aux letres "messages"
	//	msgQRece:'ve{...);
		
		// On écrit sur la scoket
		write(s,(char *) &myRequest, sizeof (myRequest));
	}
	
}
