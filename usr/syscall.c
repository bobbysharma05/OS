#include "user.h"
#include <stdarg.h>

// Updated function name and parameter order to match kernel
int get_proc_info_by_index(int index, struct proc_info *info) {
    return syscall(24, index, info);  // SYS_GET_PROC_INFO
}

// Keep the old function for compatibility if needed
int get_proc_info(struct proc_info *info, int index) {
    return get_proc_info_by_index(index, info);
}

int uprintf(int fd, const char *fmt, ...) {
    char buf[256]; // Buffer for formatted string
    va_list ap;
    va_start(ap, fmt);
    
    // Simple formatting (supports %d, %s; expand if needed)
    int len = 0;
    for (int i = 0; fmt[i] && len < sizeof(buf) - 1; i++) {
        if (fmt[i] != '%') {
            buf[len++] = fmt[i];
            continue;
        }
        i++;
        if (fmt[i] == 'd') {
            int val = va_arg(ap, int);
            char num[16];
            int j = 0;
            if (val == 0) num[j++] = '0';
            while (val) {
                num[j++] = '0' + (val % 10);
                val /= 10;
            }
            for (j--; j >= 0 && len < sizeof(buf) - 1; j--)
                buf[len++] = num[j];
        } else if (fmt[i] == 's') {
            char *s = va_arg(ap, char*);
            for (int j = 0; s[j] && len < sizeof(buf) - 1; j++)
                buf[len++] = s[j];
        }
    }
    buf[len] = '\0';
    va_end(ap);

    return syscall(22, fd, buf, len); // SYS_write
}