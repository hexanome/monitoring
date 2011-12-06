#ifndef _DEFS_H
#define _DEFS_H

#define MAX_BAD_PARTS 10
typedef struct{
	int type;
	long long time; //timestamp when part has been detected
} part;

typedef struct{
	int size;
	int partsType;
	int partsNb;
	int badParts;
} box;
#endif
