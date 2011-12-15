#include <stdio.h>
#include <unistd.h>
#include <taskLib.h>
#include <semLib.h>

#include "usine.h"
#include "mere.h"
#include "capteur.h"

static int nextBadPart=0;
static SEM_ID semBadPart;
static int badPlastic=0;
static SEM_ID semBadPlastic;
static int nextBadBox=0;
static SEM_ID semBadBox;
static int nextBadPack=0;
static SEM_ID semBadPack;
static int badPrinter=0;
static SEM_ID semBadPrinter;
#ifndef test
static int partProdTid=0;
static void startPartProd(int type);
#endif

int plastic(){
	int ret;
	semTake(semBadPlastic,WAIT_FOREVER);
	ret=badPlastic;
	semGive(semBadPlastic);
	return ret;
}
int getPrinterStatus(){
	int ret=0;
	semMTake(semBadPrinter,WAIT_FOREVER);
	ret=badPrinter;
	semGive(semBadPrinter);
	return ret;
}
int print(int batchNb, int partsNb, int partsType, int timestamp){
	char toPrint[140];
	sprintf(toPrint ,"%d : Impression du lot no %d, contenant %d pieces, de type %d",\
			timestamp, batchNb, partsNb, partsType);
	return 0;
}
int isBoxPresent(){
	int ret=0;
	semMTake(semBadBox,WAIT_FOREVER);
	ret=nextBadBox;
	semGive(semBadBox);
	return ret;
}
int isPackPresent(){
	int ret=0;
	semMTake(semBadPack,WAIT_FOREVER);
	ret=nextBadPack;
	semGive(semBadPack);
	return ret;
}
void closeTrap(){
	if (partProdTid!=0){return;}
	taskSuspend(partProdTid);
}
void openTrap(){
	if (partProdTid!=0){return;}
	taskResume(partProdTid);
}

#ifndef test
static void startPartProd(int type)
#else
void startPartProd(int type)
#endif
{
	for (;;)
	{
    	semMTake(semBadPart,WAIT_FOREVER);
		if (nextBadPart==1){
        	semGive(semBadPart);
			partType=0;
			nextBadPart=0;
		}else{
        	semGive(semBadPart);
    		partType=type;
		}
		isrCapteur();
		sleep(2);
	}
}
int launchFatory()
{
	int ret;
	int tidMain=0;
	semBadBox=semMCreate(0);
	semBadPlastic=semMCreate(0);
	semBadPack=semMCreate(0);
	semBadPart=semMCreate(0);
	semBadPrinter=semMCreate(0);
	for (;;)
	{
		printf("1) Demarrer la production des pieces de type 1\n");
		printf("2) Demarrerla production des pieces de type 2\n");
		printf("3) Arreter la production de pieces\n");
		printf("4) Generer une mauvaise piece\n");
		printf("5) Empecher le prochain carton d'arriver\n");
		printf("6) Empecher la prochaine palette d'arriver\n");
		printf("7) Generer un arret d'urgence\n");
		printf("8) Generer un probleme d'imprimante\n");
		printf("9) Generer un probleme de pose de plastique\n");
		printf("10) Lancer la surveillance du condionemment\n");
		printf("11) Quitter\n\n");
		
		for (scanf("%d",&ret); ret<1 && ret>10; scanf("%d",&ret));
		
		switch(ret)
		{
		case 1:
			if (partProdTid!=0){break;}
			partProdTid=taskSpawn("partProd1",5,0,10000,(FUNCPTR)startPartProd,1,0,0,0,0,0,0,0,0,0);
			printf("Lancement de la production de pieces de type 1\n\n");
			break;
		case 2:
			if (partProdTid!=0){break;}
			partProdTid=taskSpawn("partProd2",5,0,10000,(FUNCPTR)startPartProd,2,0,0,0,0,0,0,0,0,0);
			printf("Lancement de la production de pieces de type 2\n\n");
			break;
		case 3:
			if (partProdTid==0){break;}
			taskDelete(partProdTid);
			partProdTid=0;
			printf("Arret de la production\n\n");
			break;
		case 4:
        	semMTake(semBadPart,WAIT_FOREVER);
			nextBadPart=1;
        	semGive(semBadPart);
			printf("La prochaine piece generee sera defecueuse\n\n");
			break;
		case 5:
        	semMTake(semBadBox,WAIT_FOREVER);
			nextBadBox=1;
        	semGive(semBadBox);
			printf("Le prochain carton ne sera pas la\n\n");
			break;
		case 6:
        	semMTake(semBadPack,WAIT_FOREVER);
			nextBadPack=1;
        	semGive(semBadPack);
			printf("La prochaine palette ne sera pas la.\n\n");
			break;
		case 7:
        	printf("Envoi d'un arret d'urgence\n\n");
        	isrEmergencyStop();
			break;
		case 8:
        	semMTake(semBadPrinter,WAIT_FOREVER);
			badPrinter=1;
        	semGive(semBadPrinter);
			printf("La prochaine impression echouera\n\n");
			break;
		case 9:
			semTake(semBadPlastic,WAIT_FOREVER);
			badPlastic=-1;
			semGive(semBadPlastic);
			printf("La prochaine pose de plastique sur une palette echouera\n\n");
		case 10:
			tidMain = taskSpawn("main",10,0,30000,(FUNCPTR)main,0,0,0,0,0,0,0,0,0,0);
			break;
		case 11:
			taskDelete(partProdTid);
			taskDelete(tidMain);
			semDelete(semBadBox);
			semDelete(semBadPlastic);
			semDelete(semBadPart);
			semDelete(semBadPack);
			semDelete(semBadPrinter);
			return 0;
		}
	}
	return 0;
}
