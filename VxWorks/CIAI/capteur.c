#include "defs.h"
#include "mere.h"
#include <msgQLib.h>
void isrCapteur()
{
	//some new part has been detected
	int partType=1; //part type is 1
	part newPart;
	newPart.type=1;
	msgQSend(mid_received_part,(char*)&newPart,sizeof(newPart),NO_WAIT,MSG_PRI_NORMAL);
}
void isrEmergencyStop()
{
	//someome pushed the emergency stop button
	error("Emergency stop set!",'e');
}
