#include "server_register.h"
void server_register(int fd)
{
    LR_INFO info;
    int check = read(fd, &info, sizeof(LR_INFO));
    if(check == -1)
    {
        perror("The server fails to read the register request.\n");
        exit(EXIT_FAILURE);
    }
    printf("Preparing for registering...\n");
    printf("username: %s\npassword: %s\n", info.username, info.password);

    /* write feedback to the user */
    char user_fifo_name[BUF_SZ];
    char feedback[BUF_SZ] = "Register successfully!";
    sprintf(user_fifo_name, "/tmp/client_fifo_%s", info.username);
    int user_fifo_fd = open(user_fifo_name, O_WRONLY);
    if(user_fifo_fd == -1)
    {
        perror("The server fails to open fifo");
        exit(EXIT_FAILURE);
    }
    int check_success = write(user_fifo_fd, feedback, strlen(feedback) + 1);
    if(check_success == -1)
    {
        perror("The server fails to write feedback to the user");
        exit(EXIT_FAILURE);
    }

}