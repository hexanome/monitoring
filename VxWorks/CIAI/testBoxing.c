#include <stdio.h>
#include <msgQLib.h>
#include <taskLib.h>
#include <usrLib.h>
#include <errnoLib.h>
#include "usine.h"
#include "defs.h"
//#include "mere.h"
#include "tasks.h"

int testBoxing(){
#ifdef test
	box toFill = {5,1,0,0,42};
	box done;
	int ret = 0;
	MSG_Q_ID mid_boxing_todo = msgQCreate(10,4,0); 
	MSG_Q_ID mid_boxing_done = msgQCreate(10,4,0); 
	MSG_Q_ID mid_received_part = msgQCreate(10,4,0); 
	printf("Starting conditionning");
	startBoxing();
	
	printf("Asking for batch production : \n");
	printf("\tBatchNumber=%d\n",toFill.batchNumber);
	printf("\tBoxSize=%d\n",toFill.size);
	printf("\tPartsType=%d\n",toFill.partsType);
	ret=msgQSend(mid_boxing_todo,(char*)&toFill,sizeof(toFill),WAIT_FOREVER,MSG_PRI_NORMAL);
	if(ret==ERROR){
		printf("[FAIL],");
		printErrno(errnoGet());
		printf("\n");
		return;
	}
	printf("[OK]\n");
	printf("Starting part type 1 generation...");
	if (partProdTid!=0){
		printf("[FAIL], Production already started.\n");
		return;
	}
	partProdTid=taskSpawn("partProd1",5,0,10000,(FUNCPTR)startPartProd,1,0,0,0,0,0,0,0,0,0);
	printf("[OK]\n");
	for(;;){
    	printf("Waiting for boxes done...\n");
    	if (msgQReceive(mid_boxing_done,(char*)&done,sizeof(done),5)==-1){
    		return 1;
    	}
    	printf("Received :\n");
    	printf("\t Box size : %d\n",done.size);
    	printf("\t Part type : %d\n",done.partsType);
	}
#else
	printf("You must compile the application with 'test' defined to use this functionality!\n");
#endif
	return 0;
}