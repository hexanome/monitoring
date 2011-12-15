#ifndef __TASKS_H
#define __TASKS_H

/*This task will be in charge of puting the right parts into boxes, log finished boxes
 * and manage errors in the folowing cases :
 * >Too much bad parts
 * >No boxes
 * >Bad printer state
 */
int startBoxing();
int startWarehouse();
void startWriteFile();
void startWriteSocket();
int startPackaging();
void startRead();

#endif
