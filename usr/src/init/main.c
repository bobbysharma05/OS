#include "../../user.h"

int main(void)
{
    int pid, wpid;
    
    uprintf(1, "init: starting shell\n");
    
    while(1) {
        pid = fork();
        if(pid < 0) {
            uprintf(1, "init: fork failed\n");
            exit(1);
        }
        if(pid == 0) {
            exec("sh", (char*[]){"sh", 0});
            uprintf(1, "init: exec sh failed\n");
            exit(1);
        }
        while((wpid = wait(0)) >= 0 && wpid != pid)
            uprintf(1, "zombie!\n");
    }
}
