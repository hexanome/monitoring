#include <msgQLib.h>
#include <stdio.h>
#include "mere.h"
#include "defs.h"

int startPackaging()
{
	message batch;
	//Read from lot
	msgQReceive(mid_batch,batch,sizeof(message));
	return 0;
}