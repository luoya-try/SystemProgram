#include "client_register.h"
#define  Continue {sleep(2); system("clear"); continue;}
char myfifo_name[MYFIFO_NAME_SZ];
void handler(int sig)
{
    unlink(myfifo_name);
    exit(1);
}
int main()
{
    signal(SIGKILL, handler);
    signal(SIGINT, handler);
    signal(SIGTERM, handler);
    while(1)
    {
        printf("Please enter a single character to select the required service.\n \
                ====================\n \
                ==   R: Register  ==\n \
                ==   L: Login     ==\n \
                ==   E: Exit      ==\n \
                ====================\n");
        char op[4];
        fgets(op, 4, stdin);
        if(strlen(op) > 2 || (op[0] != 'E' && op[0] != 'L' && op[0] != 'R'))
        {
            printf("Input 'R' to register, 'E' to exit or 'L' to login. Please retry!\n");
            Continue
        }
        switch (op[0])
        {
            case 'E': 
                printf("Thank you for choosing our service. Bye~\n");
                return 0;
            case 'R': 
                client_register(myfifo_name);
                break;
            case 'L':
                break;
        }
    }
    return 0;
}