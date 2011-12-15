#ifndef _DEFS_H
#define _DEFS_H
 
#define ORDER 0 //used for batchType in struct batch
#define PROD 1
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
	int batchNumber;
} box;
typedef struct{
	int batchType; //If batch type is 1, this is a production, if it's 0, it's an order
	int nbPack1;
	int nbPack2;
	int batchNumber;
} batch;

typedef char message[140];
#endif
