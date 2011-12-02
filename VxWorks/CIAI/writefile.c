#include "writefile.h"

void startwritefile()
{
	//provisoire, à supprimer
	MSG_Q_ID msgQId;
		
	// Message d'erreur
	char *erreur;
	
	char buffer[] = { 'x' , 'y' , 'z' };
		
	FILE * mes ;
	mes = fopen ("messages","newmessages");
	
	// Boucle infini de la tache
	for (;;)
	{
		//On attend un message de la boite aux letres "messages"
		msgQReceive(msgQId ,erreur, sizeof (&erreur), WAIT_FOREVER);
			
		// On rajoute le message d'erreur dans le fichier "messages"
		fwrite (buffer , 1 , sizeof(buffer) , mes );	
	}
	fclose (mes);
}
