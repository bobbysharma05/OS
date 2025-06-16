#ifndef INC_SYSCALL_H
#define INC_SYSCALL_H

// System call numbers
#define SYS_set_tid_address 1
#define SYS_gettid 2
#define SYS_ioctl 3
#define SYS_rt_sigprocmask 4
#define SYS_brk 5
#define SYS_mmap 6
#define SYS_execve 7
#define SYS_sched_yield 8
#define SYS_clone 9
#define SYS_wait4 10
#define SYS_exit_group 11
#define SYS_exit 12
#define SYS_dup 13
#define SYS_pipe2 14
#define SYS_chdir 15
#define SYS_fstat 16
#define SYS_newfstatat 17
#define SYS_mkdirat 18
#define SYS_mknodat 19
#define SYS_openat 20
#define SYS_writev 21
#define SYS_read 22
#define SYS_close 23
#define SYS_GET_PROC_INFO 24
#define SYS_write 25

#ifndef __ASSEMBLER__
// Process info structure for kernel use (only for C code, not assembly)
typedef struct {
    int pid;
    char name[32];
    char state;
} proc_info_t;
#endif /* __ASSEMBLER__ */

#endif /* INC_SYSCALL_H */