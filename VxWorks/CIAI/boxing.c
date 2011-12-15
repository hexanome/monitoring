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
	for(;;){
		box toFill = {0,0,0,0}; //Create new empty box
		part newPart = {0,0};
		struct timespec timev;
		//See what kind of box we have to fill :
		if (msgQReceive(mid_boxing_todo,(char*)&toFill,sizeof(toFill),WAIT_FOREVER==-1)){
			printErrno(errnoGet());
			return -1;
		}
		
		for(toFill.partsNb=0; toFill.partsNb<toFill.size;){
			//Wait until some message can be read
			if (msgQReceive(mid_received_part,(char*)&newPart,sizeof(newPart),WAIT_FOREVER)==-1){
    			printErrno(errnoGet());
    			return -1;
			}
			if (isBoxPresent()==0){
				//Error no box available
				error("Erreur : aucun carton disponible",'b');
			}
			if (newPart.type==toFill.partsType){
				toFill.partsNb++;
			} else {
				toFill.badParts++;
				if(toFill.badParts >= MAX_BAD_PARTS){
					//Error too much bad parts in this box
					error("Erreur : seuil maximal de mauvaises pieces atteint",'b');
				}
			}
			clock_gettime(CLOCK_REALTIME, &timev);
			print(toFill.batchNumber,toFill.partsNb,toFill.partsType,timev.tv_sec);
		}
		//Box has been filled.
		//Is there a working printer?
		if(getPrinterStatus()==0){
			//Error we can't print right now
			error("Erreur : Imprimante inutilisable",'b');
		}
		if(msgQSend(mid_boxing_done,(char*)&toFill,sizeof(toFill),NO_WAIT,MSG_PRI_NORMAL)==-1){
			printErrno(errnoGet());
			return -1;
		}
		
	}
}

