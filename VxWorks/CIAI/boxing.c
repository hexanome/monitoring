#include <msgQLib.h>
#include "boxing.h"


#include "fakeMere.h"
#include "defs.h"
int startBoxing(){
	
	for(;;){
		box toFill = {0,0,0,0};
		part newPart = {0,0};
		//See what kind of box we have to fill :
		msgQReceive(mid_boxing_todo,(char*)&toFill,sizeof(toFill),WAIT_FOREVER);
		
		for(toFill.partsNb=0; toFill.partsNb<toFill.size;){
			//Wait until some message can be read
			msgQReceive(mid_received_part,(char*)&newPart,sizeof(newPart),WAIT_FOREVER);
			if (newPart.type==toFill.partsType){
				toFill.partsNb++;
			} else {
				toFill.badParts++;
				if(toFill.badParts >= MAX_BAD_PARTS){
					//Error
				}
			}
		}
		
		//Box has been filled.
		//Is there a working printer?
		
	}
}
