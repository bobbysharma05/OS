
#include "../../user.h"
// Removed: #include <stdlib.h>

int main(void)
{
    proc_info_t info;
    int index = 0;

    uprintf(1, "PID   STATE     NAME\n");
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
