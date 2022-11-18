#include "server_register.h"
int max(int a, int b) {return a > b ? a : b;}
void handler(int sig)
{
    unlink(register_fifo_name);
    unlink(login_fifo_name);
    unlink(message_fifo_name);
    exit(1);
}
int main()
{
    signal(SIGKILL, handler);
    signal(SIGINT, handler);
    signal(SIGTERM, handler);
    
    if(access(register_fifo_name, F_OK) == -1) CreateFifo(register_fifo_name);
    if(access(login_fifo_name, F_OK) == -1) CreateFifo(login_fifo_name);
    if(access(message_fifo_name, F_OK) == -1) CreateFifo(message_fifo_name);
    
    int register_fifo_fd = OpenRDWR(register_fifo_name);
    int login_fifo_fd = OpenRDWR(login_fifo_name);
    int message_fifo_fd = OpenRDWR(message_fifo_name);

    int mxfdp = max(register_fifo_fd, max(message_fifo_fd, login_fifo_fd));

    fd_set read_set;
    while(1)
    {
        FD_ZERO(&read_set);
        FD_SET(register_fifo_fd, &read_set);
        FD_SET(login_fifo_fd, &read_set);
        FD_SET(message_fifo_fd, &read_set);

        select(mxfdp + 1, &read_set, NULL, NULL, NULL);
        if(FD_ISSET(register_fifo_fd, &read_set)) 
            server_register(register_fifo_fd);

    }
            
    
    return 0;
}