#ifndef _HELPER_H_
#define _HELPER_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include "../helper/info.h"
#include "../helper/helper.h"
void CreateFifo(char *fifo_name);
int OpenRDWR(char *fifo_name);
int username_exist(char *username);
extern char *register_fifo_name;
extern char *login_fifo_name;
extern char *message_fifo_name;

#endif