#ifndef __USINE_H
#define __USINE_H


//device api:
int getPrinterStatus();
int isBoxPresent();
int isPackPresent();
void closeTrap();
void openTrap();
//Fake register :
int partType;


#endif