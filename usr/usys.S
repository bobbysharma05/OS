.global syscall
syscall:
    mov x8, x0     // Syscall number
    mov x0, x1     // First argument
    mov x1, x2     // Second argument
    svc #0         // Supervisor call
    ret