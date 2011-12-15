#include <stdio.h>
#include <msgQLib.h>
#include "mere.h"
#include "defs.h"
#include "time.h"
void startWriteFile()
{
	// Message d'erreur
	message erreur;
	struct timespec timev;
	
	// Boucle infini de la tache
	for (;;)
	{
		// On attend un message de la boite aux letres "messages pour fichier"
		msgQReceive(mid_log_file ,erreur, sizeof (message), WAIT_FOREVER);
			
		clock_gettime(CLOCK_REALTIME, &timev);
		// On rajoute le message d'erreur dans le fichier "messages"
		fprintf(message_file,"%d : %s\n",timev.tv_sec,erreur);
	}
}
