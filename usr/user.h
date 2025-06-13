#ifndef USER_H
#define USER_H

#include <sys/types.h>
#include <stdarg.h>

struct proc_info {
    int pid;
    char state;
    char name[16];  
};

int syscall(int num, ...);
int get_proc_info_by_index(int index, struct proc_info *info);  
int get_proc_info(struct proc_info *info, int index);          
void exit(int status);
int uprintf(int fd, const char *fmt, ...);

#endif