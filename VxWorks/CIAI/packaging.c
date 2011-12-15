#include <msgQLib.h>
#include <stdio.h>
#include "mere.h"
#include "defs.h"
#include "usine.h"

int startPackaging()
{
	batch toDo;
	pack done;
	int pack1Done=0;
	int pack2Done=0;
	box nextBoxesTodo;
	box lastDone;
	for(;;){
    	//Read from mid_batch to see what we have to produce.
    	msgQReceive(mid_batch,(char*)&toDo,sizeof(message),WAIT_FOREVER);
    	//Tell it's job to the boxing
    	if (toDo.nbPack1!=0){
        	nextBoxesTodo.partsType=1;
        	nextBoxesTodo.boxNumber=toDo.nbPack1*BOXPERPACK;
        	nextBoxesTodo.batchNumber=toDo.batchNumber;
        	nextBoxesTodo.size=PARTPERBOX;
        	msgQSend(mid_boxing_todo,(char*)&nextBoxesTodo,sizeof(box),WAIT_FOREVER,MSG_PRI_NORMAL);
    	}
    	//Create all type 1 packs
    	done.batchNumber=toDo.batchNumber;
    	done.size=BOXPERPACK;
    	done.partType=1;
    	if (isPackPresent()!=0){
    		error("No pack present",'p');
    	}
    	for (pack1Done=0; pack1Done<toDo.nbPack1; ){
    		//fill this pack :
    		for(done.boxNumber=0; done.boxNumber<done.size; done.boxNumber++){
        		msgQReceive(mid_boxing_done,(char*)&lastDone,sizeof(lastDone),WAIT_FOREVER);
    		}
    	}
    	
    	if (toDo.nbPack2!=0){
        	nextBoxesTodo.partsType=2;
        	nextBoxesTodo.boxNumber=toDo.nbPack2*BOXPERPACK;
        	nextBoxesTodo.batchNumber=toDo.batchNumber;
        	nextBoxesTodo.size=PARTPERBOX;
        	msgQSend(mid_boxing_todo,(char*)&nextBoxesTodo,sizeof(box),WAIT_FOREVER,MSG_PRI_NORMAL);
    	}
	}
	return 0;
}