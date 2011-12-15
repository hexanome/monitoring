#include <msgQLib.h>
#include <taskLib.h>
#include <errnoLib.h>
#include <usrLib.h>
#include <time.h>
#include <stdio.h>
#include "boxing.h"
#include "usine.h"
#include "mere.h"
#include "defs.h"
#ifdef test
	#include "testBoxing.h"
#endif
//TODO : Whatchdog 

int dummy(){
	return 0;
}
int startBoxing(){
	int boxNumber=0;
	box toFill = {0,0,0,0,0}; //Create new empty box
	box filled;
	part newPart = {0,0};
	struct timespec timev;
	for(;;){
		//See what kind of box we have to fill :
#ifdef test
		printf("Waiting for orders.\n");
#endif
		if (msgQReceive(mid_boxing_todo,(char*)&toFill,sizeof(toFill),WAIT_FOREVER==-1)){
			printErrno(errnoGet());
			return -1;
		}
#ifdef test
		printf("Orders received.\n");
#endif
		for(boxNumber=0; boxNumber<toFill.boxNumber;boxNumber++){
			//Loop until all the boxes are done, then get new orders.
			filled.badParts=0; //still no bad ones
			filled.batchNumber=toFill.batchNumber;
			filled.boxNumber=boxNumber;
			filled.partsType=toFill.partsType;
			filled.size=toFill.size;
    		for(filled.partsNb=0; filled.partsNb<filled.size;){
    			//Wait until some message can be read
    			if (msgQReceive(mid_received_part,(char*)&newPart,sizeof(newPart),WAIT_FOREVER)==-1){
        			printErrno(errnoGet());
        			return -1;
    			}
#ifdef test
        		printf("Part received\n");
#endif
    			if (isBoxPresent()!=0){
    				//Error no box available
    				error("Erreur : aucun carton disponible",'b');
    			}
    			if (newPart.type==toFill.partsType){
    				filled.partsNb++;
    			} else {
    				filled.badParts++;
    				if(filled.badParts >= MAX_BAD_PARTS){
    					//Error too much bad parts in this box
    					error("Erreur : seuil maximal de mauvaises pieces atteint",'b');
    				}
    			}
    			clock_gettime(CLOCK_REALTIME, &timev);
    			print(filled.batchNumber,filled.partsNb,filled.partsType,timev.tv_sec);
    		}
    		//Box has been filled.
    		//Is there a working printer?
    		if(getPrinterStatus()==0){
    			//Error we can't print right now
    			error("Erreur : Imprimante inutilisable",'b');
    		}
    		if(msgQSend(mid_boxing_done,(char*)&filled,sizeof(filled),NO_WAIT,MSG_PRI_NORMAL)==-1){
    			printErrno(errnoGet());
    			return -1;
    		}
		}	
	}
}

