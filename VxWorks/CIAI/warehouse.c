#include "warehouse.h"

int startWarehouse()
{
	int num_package_type1 = 0;
	int num_package_type2 = 0;
	char * message_commande = "";	
	char * package;
	int i = 0;
	int num_package = 0;
	
	for (;;)
	{
		// On attend un message de la boite aux letres "palettes finies" = mid_packaging
		msgQReceive(mid_packaging ,package, sizeof (&package), WAIT_FOREVER);
		
		// On récupère le nombre de palette du type donné
		for (i = 6; i < 9; i++)
		{
			num_package += (int) package[i];
			num_package *= 256;
		}
		num_package += (int) package[9];
		
		// On regarde s'il s'agit d'une commande et si elle est prête
		if ((num_package_type1 > -1)&(num_package_type2 > -1))
		{
			// On rajoute un message dans la boite aux lettres "messages" = mid_log
			message_commande = "Commande prête";
			msgQSend(mid_log, message_commande, strlen(message_commande), NO_WAIT, MSG_PRI_NORMAL);
		}
		
	}
}
