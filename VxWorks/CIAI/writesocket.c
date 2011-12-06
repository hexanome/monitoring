#include "writesocket.h"

void startWriteSocket()
{	
	// Message d'erreur
	char *erreur;
			
	// Boucle infini de la tache
	for (;;)
	{
		//On attend un message de la boite aux letres "messages"
		msgQReceive(mid_log ,erreur, sizeof (&erreur), WAIT_FOREVER);
		
		// On écrit sur la socket
		write(sock, erreur, sizeof (erreur));
	}	
}
