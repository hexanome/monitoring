#include "stdio.h"
#include "sockLib.h"

// faire du tri dans les includes inutiles
#include "vxWorks.h"
#include "inetLib.h"
#include "stdioLib.h"
#include "strLib.h"
#include "hostLib.h"
#include "ioLib.h"


#define SERVER_PORT_NUM 5001

void writes()
{
	
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
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

//	myRequest.msgLen = 5;
	//myRequest.message = "coucou";
	
	for (;;)
	{
		//write(s,(char *) &myRequest, sizeof (myRequest));
	}
	
}
