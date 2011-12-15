#include <stdio.h>
#include <unistd.h>
#include <taskLib.h>
#include <semLib.h>

#include "usine.h"
#include "mere.h"
#include "capteur.h"

static int nextBadPart=0;
static SEM_ID semBadPart;
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
	semBadPack=semMCreate(0);
	semBadPart=semMCreate(0);
	semBadPrinter=semMCreate(0);
	for (;;)
	{
		printf("1) Start type 1 part production\n");
		printf("2) Start type 2 part production\n");
		printf("3) Stop part production\n");
		printf("4) Generate next part as a bad one\n");
		printf("5) Prevent next box from spawning\n");
		printf("6) Prevent next pack from spawning\n");
		printf("7) Generate an emergency stop\n");
		printf("8) Generate a printer problem\n");
		printf("9) Start monitoring\n");
		printf("10) Exit\n\n");
		
		for (scanf("%d",&ret); ret<1 && ret>10; scanf("%d",&ret));
		
		switch(ret)
		{
		case 1:
			if (partProdTid!=0){break;}
			partProdTid=taskSpawn("partProd1",5,0,10000,(FUNCPTR)startPartProd,1,0,0,0,0,0,0,0,0,0);
			printf("Starting type 1 part production\n\n");
			break;
		case 2:
			if (partProdTid!=0){break;}
			partProdTid=taskSpawn("partProd2",5,0,10000,(FUNCPTR)startPartProd,2,0,0,0,0,0,0,0,0,0);
			printf("Starting type 2 part production\n\n");
			break;
		case 3:
			if (partProdTid==0){break;}
			taskDelete(partProdTid);
			partProdTid=0;
			printf("Stoping part production\n\n");
			break;
		case 4:
        	semMTake(semBadPart,WAIT_FOREVER);
			nextBadPart=1;
        	semGive(semBadPart);
			printf("Next part will be a bad one\n\n");
			break;
		case 5:
        	semMTake(semBadBox,WAIT_FOREVER);
			nextBadBox=1;
        	semGive(semBadBox);
			printf("Next box won't be present\n\n");
			break;
		case 6:
        	semMTake(semBadPack,WAIT_FOREVER);
			nextBadPack=1;
        	semGive(semBadPack);
			printf("Next pack won't be present\n\n");
			break;
		case 7:
        	printf("Sending an emergency stop\n\n");
        	isrEmergencyStop();
			break;
		case 8:
        	semMTake(semBadPrinter,WAIT_FOREVER);
			badPrinter=1;
        	semGive(semBadPrinter);
			printf("Next printer status check call will return error\n\n");
			break;
		case 9:
			tidMain = taskSpawn("main",10,0,30000,(FUNCPTR)main,0,0,0,0,0,0,0,0,0,0);
			break;
		case 10:
			taskDelete(partProdTid);
			taskDelete(tidMain);
			semDelete(semBadBox);
			semDelete(semBadPart);
			semDelete(semBadPack);
			semDelete(semBadPrinter);
			return 0;
		}
	}
	return 0;
}
