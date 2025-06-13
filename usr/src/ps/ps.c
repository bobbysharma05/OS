#include "usr/user.h"

int
main(void)
{
    struct proc_info info;
    int index = 0;

    uprintf(1, "PID   STATE     NAME\n"); // fd 1 = stdout
    while (get_proc_info_by_index(index, &info) == 0) {
        char *state_str;
        switch (info.state) {
            case 'E': state_str = "EMBRYO"; break;
            case 'S': state_str = "SLEEPING"; break;
            case 'R': state_str = "RUNNABLE"; break;
            case 'U': state_str = "RUNNING"; break;
            case 'Z': state_str = "ZOMBIE"; break;
            default: state_str = "UNKNOWN";
        }
        uprintf(1, "%-6d %-10s %s\n", info.pid, state_str, info.name);
        index++;
    }

    exit(0);
}