#include "writesocket.h"
//#include "mere.h"

void startWriteSocket()
{
	//provisoire, � supprimer
	 MSG_Q_ID msgQId;
	
	// Message d'erreur
	char *erreur;
			
	// Boucle infini de la tache
	for (;;)
	{
		//On attend un message de la boite aux letres "messages"
		msgQReceive(msgQId ,erreur, sizeof (&erreur), WAIT_FOREVER);
		
		// On �crit sur la socket
		//write(sock, erreur, sizeof (erreur));
	}	
}
