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
    	done.number=toDo.batchNumber;
    	done.size=BOXPERPACK;
    	
    	//Tell it's job to the boxing
    	//Create all type 1 packs
    	if (toDo.nbPack1!=0){
        	nextBoxesTodo.partsType=1;
        	nextBoxesTodo.boxNumber=toDo.nbPack1*BOXPERPACK;
        	nextBoxesTodo.batchNumber=toDo.batchNumber;
        	nextBoxesTodo.size=PARTPERBOX;
        	msgQSend(mid_boxing_todo,(char*)&nextBoxesTodo,sizeof(box),WAIT_FOREVER,MSG_PRI_NORMAL);
    	}
    	//Create all type 2 packs
    	if (toDo.nbPack2!=0){
        	nextBoxesTodo.partsType=2;
        	nextBoxesTodo.boxNumber=toDo.nbPack2*BOXPERPACK;
        	nextBoxesTodo.batchNumber=toDo.batchNumber;
        	nextBoxesTodo.size=PARTPERBOX;
        	msgQSend(mid_boxing_todo,(char*)&nextBoxesTodo,sizeof(box),WAIT_FOREVER,MSG_PRI_NORMAL);
    	}
    	//Get all type 1 parts
    	done.nbType1=1;
    	done.nbType2=0;
    	for (pack1Done=0; pack1Done<toDo.nbPack1; ){
    		//Test if there is a pack
        	if (isPackPresent()!=0){
        		error("Erreur : aucunne palette presente.",'p');
        	}
    		//fill this pack :
    		for(done.boxNumber=0; done.boxNumber<done.size; done.boxNumber++){
        		msgQReceive(mid_boxing_done,(char*)&lastDone,sizeof(lastDone),WAIT_FOREVER);
    		}
        	//pack filled
    		//Try to plasticize it
    		if (plastic()==-1){
    			error("Erreur : la mise sous plastique a echouee.",'p');
    		}
    		//Send it to the warehouse :
    		msgQSend(mid_packaging,(char*)&done,sizeof(done),WAIT_FOREVER,MSG_PRI_NORMAL);
    	}
    	
    	//Get all type 2 parts
    	done.nbType1=0;
    	done.nbType2=1;
    	for (pack2Done=0; pack2Done<toDo.nbPack2; ){
    		//Test if there is a pack
        	if (isPackPresent()!=0){
        		error("Erreur : aucunne palette presente.",'p');
        	}
    		//fill this pack :
    		for(done.boxNumber=0; done.boxNumber<done.size; done.boxNumber++){
        		msgQReceive(mid_boxing_done,(char*)&lastDone,sizeof(lastDone),WAIT_FOREVER);
    		}
        	//pack filled
    		//Try to plasticize it
    		if (plastic()==-1){
    			error("Erreur : la mise sous plastique a echouee.",'p');
    		}
    		//Send it to the warehouse :
    		msgQSend(mid_packaging,(char*)&done,sizeof(done),WAIT_FOREVER,MSG_PRI_NORMAL);
    	}
	}
	return 0;
}