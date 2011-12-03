#ifndef _MERE_H
#define _MERE_H

#include <msgQLib.h>
#include <stdio.h>
MSG_Q_ID mid_boxing_todo;
MSG_Q_ID mid_boxing_done;
MSG_Q_ID mid_log;
MSG_Q_ID mid_packing;
MSG_Q_ID mid_patch;
MSG_Q_ID mid_boxing;

int tid_boxing;
int tid_packing;
int tid_warehouse;
int tid_write;
int tid_read;
int tid_main;
FILE * message_file;

int main();

#endif