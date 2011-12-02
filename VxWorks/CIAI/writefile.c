#include "writefile.h"

void startwritefile()
{
	//provisoire, à supprimer
	MSG_Q_ID msgQId;
		
	// Message d'erreur
	char *erreur;
	
	FILE * mes ;
	
	mes = fopen ("messages","newmessages");
	
	// Boucle infini de la tache
	for (;;)
	{
		//On attend un message de la boite aux letres "messages"
		msgQReceive(msgQId ,erreur, sizeof (&erreur), WAIT_FOREVER);
		
		// On rajoute le message d'erreur dans le fichier "messages"
		
	}	
}
