#include "user.h"

extern int syscall(int num, ...);

int get_proc_info_by_index(int index, proc_info_t *info)
{
    return syscall(24, index, info); // SYS_GET_PROC_INFO = 24
}

// Simple uprintf implementation
int uprintf(int fd, const char *fmt, ...)
{
    // For now, just write the format string directly (no formatting)
    int len = 0;
    const char *s = fmt;
    
    // Calculate string length
    while(*s++) len++;
    
    return write(fd, fmt, len);
}
