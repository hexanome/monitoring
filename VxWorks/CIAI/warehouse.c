#include "warehouse.h"

// récupère un nombre dans un message
int getNumber(int start, int size)
{
	int i = 0; // utilisé dans une boucle for
	
	for (i = start; i < (start + size - 1); i++)
			{
				num += (int) package[i];
				num *= 256;
			}
			num += (int) package[start + size];
			num_package_type1 += num;
}

int startWarehouse()
{
	int num_package_type1 = 0; // nombre de palettes de type 1 dans l'entrepot
	int num_package_type2 = 0; // nombre de palettes de type 2 dans l'entrepot
	int num_commande = -1; // le nuémro de la commande
	int num = 0; // variable intérmédiaire utilisée pour récupérer les nombres dans les messages
	char * package; // message envoyer par la boite aux lettres
	char * message_commande = ""; // messages envoyé dans la boite aux lettres "messages"	
	int i = 0; // utilisé dans une boucle for
	
	for (;;)
	{
		// On attend un message de la boite aux letres "palettes finies" = mid_packaging
		msgQReceive(mid_packaging, package, sizeof (&package), WAIT_FOREVER);
		
		// On regarde s'il s'agit d'une commande
		if (package[0] = 'c')
		{
			// On récupère le numéro de la commande
			num_commande = getNumber(1, 4);

			// On récupère le nombre de palette de type 1
			num_package_type1 -= getNumber(5, 4);
		
			// On récupère le nombre de palette de type 2
			num_package_type2 -= getNumber(9, 12);
		
			// si la commande est prête
			if ((num_package_type1 > -1)&(num_package_type2 > -1))
			{
				// On rajoute des messages dans la boite aux lettres "messages" = mid_log
				message_commande = "La commande n° " + num_commande + "est prête";
				msgQSend(mid_log, message_commande, strlen(message_commande), NO_WAIT, MSG_PRI_NORMAL);
			}
			// si la commande n'est pas prëte
			else
			{
				// On rajoute des messages dans la boite aux lettres "messages" = mid_log
				message_commande = "La commande n° " + num_commande + " n'est pas encore prête";
				msgQSend(mid_log, message_commande, strlen(message_commande), NO_WAIT, MSG_PRI_NORMAL);
			}
		}
		// On regarde s'il s'agit d'une initialisation
		if (package[0] = 'i')
		{
			// On récupère le nombre de palette de type 1
			num_package_type1 += getNumber(1, 4);
		
			// On récupère le nombre de palette de type 2
			num_package_type2 += getNumber(4, 4);
			
			// On rajoute un message dans la boite aux lettres "messages" = mid_log
			message_commande = "Initialisation : Nombre de palettes de type 1 à fabriquer : " + int num_package_type1;
			message_commande = "Initialisation : Nombre de palettes de type 2 à fabriquer : " + int num_package_type2;
			msgQSend(mid_log, message_commande, strlen(message_commande), NO_WAIT, MSG_PRI_NORMAL);
		}
	}
}
