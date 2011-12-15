#ifndef _DEFS_H
#define _DEFS_H
 
#define MAX_BAD_PARTS 10
#define PARTPERBOX 10
#define BOXPERPACK 20
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
	int boxNumber;
} box;
typedef struct{
	int nbPack1;
	int nbPack2;
	int batchNumber;
} batch;
typedef struct{
	int nbType1;
	int nbType2;
	int size;
	int number; //Either number of command, or number of batch
	int boxNumber;
} pack;

typedef char message[140];
#endif
