#include "../inc/syscall.h"

.text

.global syscall
syscall:
    mov x8, x0      // Move syscall number to x8
    mov x0, x1      // Move first argument to x0
    mov x1, x2      // Move second argument to x1
    mov x2, x3      // Move third argument to x2
    mov x3, x4      // Move fourth argument to x3
    mov x4, x5      // Move fifth argument to x4
    mov x5, x6      // Move sixth argument to x5
    svc #0          // Make system call
    ret

// Individual syscall wrappers (removed exit)
.global exec
exec:
    mov x8, #SYS_execve
    svc #0
    ret

.global fork
fork:
    mov x8, #SYS_clone
    svc #0
    ret

.global wait
wait:
    mov x8, #SYS_wait4
    svc #0
    ret

.global open
open:
    mov x8, #SYS_openat
    svc #0
    ret

.global close
close:
    mov x8, #SYS_close
    svc #0
    ret

.global write
write:
    mov x8, #SYS_writev
    svc #0
    ret
