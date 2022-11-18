#ifndef _CLIENT_REGISTER_H_
#define _CLIENT_REGISTER_H_
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
#define Continue {sleep(2); system("clear"); continue;}
void client_register(char *);
#endif