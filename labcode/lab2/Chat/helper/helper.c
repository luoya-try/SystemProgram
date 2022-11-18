#include "helper.h"
char *register_fifo_name = "/tmp/public_register_fifo";
char *login_fifo_name = "/tmp/public_login_fifo";
char *message_fifo_name = "/tmp/public_message_fifo";
void CreateFifo(char *fifo_name)
{
    int check = mkfifo(fifo_name, 0777);
    if(check == -1)
    {
        printf("FIFO %s was not created.\n", fifo_name);
        exit(EXIT_FAILURE);
    }
}
int OpenRDWR(char *fifo_name)
{
    int fd = open(fifo_name, O_RDWR);
    if(fd == -1)
    {
        printf("Could not open %s for read only access.\n", fifo_name);
        exit(EXIT_FAILURE);
    }
    return fd;
}
int username_exist(char *username)
{
    return 0;
}