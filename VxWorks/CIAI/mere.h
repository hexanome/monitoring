#ifndef __MERE_H
#define __MERE_H

#include <stdio.h>
#include <msgQLib.h>

#define SERVER_PORT_NUM 5001

MSG_Q_ID mid_boxing_todo;
MSG_Q_ID mid_boxing_done;
MSG_Q_ID mid_log;
MSG_Q_ID mid_packaging;
MSG_Q_ID mid_batch;
MSG_Q_ID mid_boxing;

int tid_boxing;
int tid_packaging;
int tid_warehouse;
int tid_writefile;
int tid_writesocket;
int tid_read;
int tid_main;

FILE * message_file;

int main();
static int createsocket();

#endif
