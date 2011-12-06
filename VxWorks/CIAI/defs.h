#ifndef _DEFS_H
#define _DEFS_H

typedef struct{
	int type;
	int time; //timestamp when part has been detected
} part;

typedef struct{
	int size;
	int partsType;
	int partsNb;
	int badParts;
} box;
#endif
