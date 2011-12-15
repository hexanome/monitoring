#include <stdio.h>
#include <sockLib.h>
#include <msgQLib.h>
#include <inetLib.h>
#include <strLib.h>
#include "mere.h"

void startWriteSocket()
{	
	// Message d'erreur
	char *erreur;
			
	// Boucle infini de la tache
	for (;;)
	{
		//On attend un message de la boite aux letres "messages"
		msgQReceive(mid_log ,erreur, sizeof (&erreur), WAIT_FOREVER);
		
		// On rajoute le message dans la boite aux lettres "messages pour fichier"
		msgQSend(mid_log_file, erreur, strlen(erreur), NO_WAIT, MSG_PRI_NORMAL);
		
		// On ecrit sur la socket
		write(sock, erreur, sizeof (erreur));
		
	}	
}
