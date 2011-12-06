#include "writefile.h"

void startWriteFile()
{
	// Message d'erreur
	char *erreur;
	
	// Boucle infini de la tache
	for (;;)
	{
		//On attend un message de la boite aux letres "messages"
		msgQReceive(mid_log ,erreur, sizeof (&erreur), WAIT_FOREVER);
			
		// On rajoute le message d'erreur dans le fichier "messages"
		fwrite (erreur, sizeof(char), strlen(erreur), message_file);	
	}
}
