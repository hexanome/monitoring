#ifndef __MERE_H
#define __MERE_H

#include <stdio.h>
#include <msgQLib.h>

// MessagesQueues ID
MSG_Q_ID mid_boxing_todo;
MSG_Q_ID mid_boxing_done;
MSG_Q_ID mid_received_part;
MSG_Q_ID mid_log;
MSG_Q_ID mid_log_file;
MSG_Q_ID mid_packaging;
MSG_Q_ID mid_batch;
MSG_Q_ID mid_actions;

// Tasks ID
int tid_boxing;
int tid_packaging;
int tid_warehouse;
int tid_writefile;
int tid_writesocket;
int tid_read;
int tid_main;

// Network part
FILE * message_file;
int sock;

// Variables
int recoverAfterCrash; //boolean 1=true 0=false

// Mutex
SEM_ID sid_recover;

// Functions declarations
int main();
void error(char * message, char sender);
void info(char * message);
#endif
