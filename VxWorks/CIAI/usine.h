#ifndef __USINE_H
#define __USINE_H

#define test
//device api:
int getPrinterStatus();
int print(int batchNb, int partsNb, int partsType, int timestamp);
int isBoxPresent();
int isPackPresent();

#ifdef test //in case it's a test, the test functions may use this api,
			//otherwise it's got to be private to usine
void startPartProd(int type);
int partProdTid;
#endif

void closeTrap();
void openTrap();
//Fake register :
int partType;


#endif