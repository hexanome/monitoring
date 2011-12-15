#include "warehouse.h"
#include "defs.h"
#include <stdio.h>

static int getNumber(int start, int size);

// recupere un nombre dans un message
int getNumber(int start, int size)
{
	int num = 0; // variable int�rm�diaire utilis�e pour r�cup�rer les nombres dans les messages
	message package; // message envoye par la boite aux lettres
	int i = 0; // utilis� dans une boucle for
	
	for (i = start; i < (start + size - 1); i++)
			{
				num += (int) package[i];
				num *= 256;
			}
			num += (int) package[start + size];
}

int startWarehouse()
{
	int num_package_type1 = 0; // nombre de palettes de type 1 dans l'entrepot
	int num_package_type2 = 0; // nombre de palettes de type 2 dans l'entrepot
	int num_commande = -1; // le nu�mro de la commande
	int num = 0; // variable int�rm�diaire utilis�e pour r�cup�rer les nombres dans les messages
	message package; // message envoye par la boite aux lettres
	char * message_commande = ""; // messages envoy� dans la boite aux lettres "messages"	
	int i = 0; // utilis� dans une boucle for
	
	for (;;)
	{
		// On attend un message de la boite aux letres "palettes finies" = mid_packaging
		msgQReceive(mid_packaging, package, sizeof (&package), WAIT_FOREVER);
		
		// On regarde s'il s'agit d'une commande
		if (package[0] == 'c')
		{
			// On r�cup�re le num�ro de la commande
			num_commande = getNumber(1, 4);

			// On r�cup�re le nombre de palette de type 1
			num_package_type1 -= getNumber(5, 4);
		
			// On r�cup�re le nombre de palette de type 2
			num_package_type2 -= getNumber(9, 12);
		
			// si la commande est pr�te
			if ((num_package_type1 > -1)&(num_package_type2 > -1))
			{
				// On rajoute des messages dans la boite aux lettres "messages" = mid_log
				sprintf(message_commande,"La commande no %d est prete",num_commande);
				printf("%s\n",message_commande);
				msgQSend(mid_log, message_commande, strlen(message_commande), NO_WAIT, MSG_PRI_NORMAL);
			}
			// si la commande n'est pas pr�te
			else
			{
				// On rajoute des messages dans la boite aux lettres "messages" = mid_log
				
				sprintf(message_commande,"La commande no %d n'est pas prete",num_commande);
				printf("%s\n",message_commande);
				msgQSend(mid_log, message_commande, strlen(message_commande), NO_WAIT, MSG_PRI_NORMAL);
			}
		}
		// On regarde s'il s'agit d'une initialisation
		if (package[0] == 'i')
		{
			// On r�cup�re le nombre de palette de type 1
			num_package_type1 += getNumber(1, 4);
		
			// On r�cup�re le nombre de palette de type 2
			num_package_type2 += getNumber(4, 4);
			
			// On rajoute un message dans la boite aux lettres "messages" = mid_log
			sprintf(message_commande,"Initialisation : Nombre de palettes de type 1 � fabriquer : %d",num_package_type1);
			sprintf(message_commande,"Initialisation : Nombre de palettes de type 2 � fabriquer : %d",num_package_type2);
			msgQSend(mid_log, message_commande, strlen(message_commande), NO_WAIT, MSG_PRI_NORMAL);
		}
	}
}
