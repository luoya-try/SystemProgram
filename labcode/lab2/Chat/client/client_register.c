#include "client_register.h"
void client_register(char *myfifo_name)
{
    LR_INFO info;
    char buffer[BUF_SZ], tmpstr[USR_SZ]; 
    memset(info.username, 0, sizeof(LR_INFO));
    /* input username and password */
    while(1)
    {
        printf("=======================Register=======================\n");
        printf("Please input your username: ");
        if(strlen(info.username)) printf("%s\n", info.username);
        else 
        {
                   
            fgets(tmpstr, USR_SZ, stdin);
            if(strlen(tmpstr) > USR_SZ - 5)
            {
                printf("The length of username should be less than 20. Please retry.\n"); 
                Continue
            } 
            else if(username_exist(tmpstr)) 
            {
                printf("Username already exists. Please retry!\n");
                Continue
            }
            else if(strlen(tmpstr) < 2)
            {
                printf("The length of username can not be empty. Please retry.\n");
                Continue
            }
            strncpy(info.username, tmpstr, strlen(tmpstr));
            info.username[strlen(tmpstr) - 1] = '\0';
        }

        printf("Please input your password: ");     
        fgets(tmpstr, PWD_SZ, stdin);
        if(strlen(tmpstr) > PWD_SZ - 5)
        {
            printf("The length of password should be less than 20. Please retry.\n"); 
            Continue
        } 
        else if(strlen(tmpstr) <= 6)
        {
            printf("The length of password can not be less than 6. Please retry.\n");
            Continue
        }
        strncpy(info.password, tmpstr, strlen(tmpstr));
        info.password[strlen(tmpstr) - 1] = '\0';
        break;
    }
    
    /* create the private fifo to get the result of register */
    int check_success, myfifo_fd;
    sprintf(myfifo_name, "/tmp/client_fifo_%s", info.username);
    CreateFifo(myfifo_name);

    /* open the register_fifo the server created */
    if(access(register_fifo_name,F_OK) == -1)
    {
        printf("Could not open FIFO %s\n", register_fifo_name);
        exit(EXIT_FAILURE);
    }
    int public_fifo_fd = open(register_fifo_name, O_WRONLY);
    LR_INFO register_info;
    
    check_success = write(public_fifo_fd, &info, sizeof(LR_INFO));
    if(check_success == -1)
    {
        perror("The client fails to write register info to the public pipe!");
        exit(EXIT_FAILURE);
    }
    close(public_fifo_fd);

    /* open myfifo for read only */
    myfifo_fd = open(myfifo_name, O_RDONLY);
    if(myfifo_fd == -1)
    {
        printf("Could not open %s for read only access\n", myfifo_name);
        exit(EXIT_FAILURE);
    }

    /* receive feedback from server */
    memset(buffer, '\0', BUF_SZ);
    check_success = read(myfifo_fd, buffer, BUF_SZ);
    if(check_success > 0)
    {
        printf("%s\n", buffer);
        //Register successfully! Back to main page ...
        //Register failed! Back to main page...
    }
    else printf("User %s can't receive any feedback from server during the registration\n", info.username);
}
