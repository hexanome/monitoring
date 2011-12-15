#include <msgQLib.h>
#include <taskLib.h>
#include <errnoLib.h>
#include <usrLib.h>
#include <time.h>
#include <stdio.h>
#include "usine.h"
#include "mere.h"
#include "defs.h"
#ifdef test
	#include "testBoxing.h"
#endif

int dummy(){ 
//this is the entry point used when load to the simulator target
//it allows us to start whichever function we want to be ran in the shell, at run time
	return 0;
}
int startBoxing(){
	int boxNumber=0; //Number of box to create.
	char log[100];
	box toFill = {0,0,0,0,0}; //Create new empty box representing the boxes to fill.
	box filled; ///Represent the boxes filled
	part newPart = {0,0}; //Part received from snesor
	struct timespec timev; //used to get timestamp from the system
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
    				filled.partsNb++; //if the part is right
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
    		//send full box to packaging
    		//Log the fact that a box was created :
    		sprintf(log,"Log : Box filled up in batch %d, %d pieces of type %d, %d bad pieces were detected",\
    				filled.batchNumber,filled.partsNb, filled.partsType, filled.badParts);
    		info(log);
    		if(msgQSend(mid_boxing_done,(char*)&filled,sizeof(filled),NO_WAIT,MSG_PRI_NORMAL)==-1){
    			printErrno(errnoGet());
    			return -1;
    		}
		}	
	}
}

