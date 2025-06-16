.section .text
.global _start
_start:
    // Infinite loop - no syscalls, no dependencies
1:  b 1b

