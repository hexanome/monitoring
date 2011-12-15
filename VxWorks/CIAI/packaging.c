#include <msgQLib.h>
#include <stdio.h>
#include "mere.h"
#include "defs.h"

int startPackaging()
{
	batch toDo;
	//Read from mid_batch to see what we have to produce.
	msgQReceive(mid_batch,(char*)&toDo,sizeof(message),WAIT_FOREVER);
	
	return 0;
}