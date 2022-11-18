#ifndef _INFO_H
#define _INFO_H
#define MYFIFO_NAME_SZ  50
#define USR_SZ 26
#define PWD_SZ 26
#define MSG_SZ 200
#define BUF_SZ 50 
typedef struct 
{
    char username[USR_SZ];
    char password[PWD_SZ];
} LR_INFO, *LR_INFO_PTR;

typedef struct
{
    char username[USR_SZ];
    char message[MSG_SZ];
} MSG_INFO, *MSG_INFO_PTR;
//public fifo_name

#endif