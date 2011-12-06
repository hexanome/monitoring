typedef struct part{
	int type;
	int time; //timestamp when part has been detected
} part;

typedef struct box{
	int size;
	int partsType;
	int partsNb;
} box;


