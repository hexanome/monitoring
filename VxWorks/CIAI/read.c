#include "stdio.h"
#include "sockLib.h"

// faire du tri dans les includes inutiles
#include "vxWorks.h"
#include "inetLib.h"
#include "stdioLib.h"
#include "strLib.h"
#include "hostLib.h"

#define SERVER_PORT_NUM 5001

void client(){
	struct sockaddr_in clientAddr;
	int clientAddrSize = sizeof (struct sockaddr_in);
	int s;
	bzero ((char *) &clientAddr, clientAddrSize);
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_len = (u_char) clientAddrSize;
	clientAddr.sin_port = htons (SERVER_PORT_NUM);
	clientAddr.sin_addr.s_addr = htonl (INADDR_ANY);
	
	s = socket(AF_INET, SOCK_STREAM, 0);
	connect(s,(struct sockaddr  *) &clientAddr,clientAddrSize);
}
