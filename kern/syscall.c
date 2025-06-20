#include "types.h"
#include "proc.h"
#include "syscall.h"
#include "memlayout.h"
#include "trap.h"
#include "console.h"
#include "debug.h"

extern int sys_brk(void);
extern int sys_mmap(void);
extern int sys_wait4(void);
extern int sys_yield(void);
extern int sys_execve(void);
extern int sys_dup(void);
extern int sys_chdir(void);
extern int sys_pipe2(void);
extern int sys_clone(void);
extern int sys_fstat(void);
extern int sys_fstatat(void);
extern int sys_openat(void);
extern int sys_mkdirat(void);
extern int sys_mknodat(void);
extern int sys_close(void);
extern int sys_writev(void);
extern int sys_read(void);
extern int sys_get_proc_info(void);
extern int sys_write(void); 
extern int sys_fexecve(void);

int
in_user(void *s, size_t n)
{
    struct proc *p = thisproc();
    if ((p->base <= (uint64_t)s && (uint64_t)s + n <= p->sz) ||
        (USERTOP - p->stksz <= (uint64_t)s && (uint64_t)s + n <= USERTOP))
        return 1;
    return 0;
}

int
fetchstr(uint64_t addr, char **pp)
{
    struct proc *p = thisproc();
    char *s;
    *pp = s = (char *)addr;
    if (p->base <= addr && addr < p->sz) {
        for (; (uint64_t)s < p->sz; s++)
            if (*s == 0)
                return s - *pp;
    } else if (USERTOP - p->stksz <= addr && addr < USERTOP) {
        for (; (uint64_t)s < USERTOP; s++)
            if (*s == 0)
                return s - *pp;
    }
    return -1;
}

int
argint(int n, int *ip)
{
    struct proc *proc = thisproc();
    if (n > 5) {
        warn("too many system call parameters");
        return -1;
    }
    *ip = proc->tf->x[n];
    return 0;
}

int
argu64(int n, uint64_t *ip)
{
    struct proc *proc = thisproc();
    if (n > 5) {
        warn("too many system call parameters");
        return -1;
    }
    *ip = proc->tf->x[n];
    return 0;
}

int
argptr(int n, char **pp, size_t size)
{
    uint64_t i = 0;
    if (argu64(n, &i) < 0)
        return -1;
    if (in_user((void *)i, size)) {
        *pp = (char *)i;
        return 0;
    }
    return -1;
}

int
argstr(int n, char **pp)
{
    uint64_t addr = 0;
    if (argu64(n, &addr) < 0)
        return -1;
    return fetchstr(addr, pp);
}

// YOUR PS COMMAND SYSCALL IMPLEMENTATION - WORKING PERFECTLY!
int
sys_get_proc_info(void)
{
    int index;
    proc_info_t kernel_info;
    uint64_t user_info_ptr;

    if (argint(0, &index) < 0 || argu64(1, &user_info_ptr) < 0)
        return -1;

    if (get_proc_info_by_index(index, &kernel_info) != 0)
        return -1;

    // Copy the structure to user space
    if (!in_user((void *)user_info_ptr, sizeof(proc_info_t)))
        return -1;

    // Direct memory copy since we're in kernel mode
    *(proc_info_t *)user_info_ptr = kernel_info;

    return 0;
}

int
syscall1(struct trapframe *tf)
{
    thisproc()->tf = tf;
    int sysno = tf->x[8];
    switch (sysno) {
    case SYS_set_tid_address:
        trace("set_tid_address: name '%s'", thisproc()->name);
        return thisproc()->pid;
    case SYS_gettid:
        trace("gettid: name '%s'", thisproc()->name);
        return thisproc()->pid;
    case SYS_ioctl:
        trace("ioctl: name '%s'", thisproc()->name);
        if (tf->x[1] == 0x5413)
            return 0;
        else
            panic("ioctl unimplemented.");
    case SYS_rt_sigprocmask:
        trace("rt_sigprocmask: name '%s' how 0x%x", thisproc()->name, (int)tf->x[0]);
        return 0;
    case SYS_brk:
        return sys_brk();
    case SYS_mmap:
        return sys_mmap();
    case SYS_execve:
        return sys_execve();
    case SYS_sched_yield:
        return sys_yield();
    case SYS_clone:
        return sys_clone();
    case SYS_wait4:
        return sys_wait4();
    case SYS_exit_group:
    case SYS_exit:
        trace("sys_exit: '%s' exit with code %d", thisproc()->name, tf->x[0]);
        exit(tf->x[0]);
    case SYS_dup:
        return sys_dup();
    case SYS_pipe2:
        return sys_pipe2();
    case SYS_chdir:
        return sys_chdir();
    case SYS_fstat:
        return sys_fstat();
    case SYS_newfstatat:
        return sys_fstatat();
    case SYS_mkdirat:
        return sys_mkdirat();
    case SYS_mknodat:
        return sys_mknodat();
    case SYS_openat:
        return sys_openat();
    case SYS_writev:
        return sys_writev();
    case SYS_read:
        return sys_read();
    case SYS_close:
        return sys_close();
    case SYS_GET_PROC_INFO:
        return sys_get_proc_info();
    case SYS_write:
        return sys_write();
    case SYS_fexecve:
        return sys_execve(); 

    default:
        debug_reg();
        panic("Unexpected syscall #%d\n", sysno);
        return 0;
    }
}
