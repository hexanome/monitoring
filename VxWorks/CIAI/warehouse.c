#include "defs.h"
#include "mere.h"
#include "usine.h"
#include <strLib.h>
#include <msgQLib.h>
#include <stdio.h>

int startWarehouse()
{
	int num_package_type1 = 0; // nombre de palettes de type 1 dans l'entrepot
	int num_package_type2 = 0; // nombre de palettes de type 2 dans l'entrepot
	int num_commande = -1; // le numero de la commande
	int num = 0; // variable intermediaire utilisee pour recuperer les nombres dans les messages
	pack package; // message envoye par la boite aux lettres
	message message_commande; // messages envoye dans la boite aux lettres "messages"	
	int i = 0; // utilise dans une boucle for
	
	for (;;)
	{
		// On attend un message de la boite aux letres "palettes finies" = mid_packaging
		//Note : cette boite aux lettre contient egalement les palettes qui doivent
		//partir de l'entrepot. Dans ce cas les membres nbType1 et 2 seront negatifs
		//pour marquer le depart de l'entrepot de plusieurs palettes, a l'inverse des 
		//messages de packaging ou il n'arrive que des palettes une par une.
		msgQReceive(mid_packaging,(char*)&package, sizeof (&package), WAIT_FOREVER);
		
		// On regarde s'il s'agit d'une commande
		if (package.nbType1<0 || package.nbType2<0)
		{
			// On recupere le numero de la commande
			num_commande = package.number;

			// si la commande est pr�te : il y a suffisament de palettes
			if ((num_package_type1+package.nbType1 > -1)&\
				(num_package_type2+package.nbType2 > -1))
			{
				// On rajoute des messages dans la boite aux lettres "messages" = mid_log
				sprintf(message_commande,"La commande no %d est prete",num_commande);
#ifdef test
				printf("%s\n",message_commande);
#endif
				msgQSend(mid_log, message_commande, sizeof(message), NO_WAIT,MSG_PRI_NORMAL);
    			// On recupere le nombre de palette voulues de type 1
    			num_package_type1 += package.nbType1;
    			// On r�cup�re le nombre de palette voulues de type 2
    			num_package_type2 += package.nbType2;
			}
			// si la commande n'est pas pr�te
			else
			{
				// On rajoute des messages dans la boite aux lettres "messages" = mid_log
				
				sprintf(message_commande," La commande no %d n'est pas prete",num_commande);
#ifdef test
				printf("%s\n",message_commande);
#endif
				msgQSend(mid_log, message_commande, sizeof(message), NO_WAIT, MSG_PRI_NORMAL);
			}
		}else{
			//Il doit donc s'agir d'une arrivee
			//On ne recoit les palettes qu'une par une 
			num_package_type1 += package.nbType1;
			num_package_type2 += package.nbType2;
			
			// On rajoute un message dans la boite aux lettres "messages" = mid_log
			sprintf(message_commande," Log : nouvelle palette dans l'entrepot de type %d",(package.nbType1==0)? 2 : 1);
			msgQSend(mid_log, message_commande, sizeof(message), NO_WAIT, MSG_PRI_NORMAL);
		}
	}
}
