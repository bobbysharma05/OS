#ifndef USER_H
#define USER_H

// Define size_t ourselves
typedef unsigned int size_t;

typedef struct {
    int pid;
    char name[32];  // FIXED: was "char name;" should be "char name[32];"
    char state;
} proc_info_t;

int get_proc_info_by_index(int index, proc_info_t *info);
int uprintf(int fd, const char *fmt, ...);
void exit(int);
int strcmp(const char*, const char*);
int exec(char*, char**);
int close(int);
int open(char*, int);
int wait(int*);
int pipe(int*);
int dup(int);
void* memset(void*, int, size_t);
char* gets(char*);
size_t strlen(const char*);
int chdir(const char*);
int fork(void);
char* strchr(const char*, int);
int write(int fd, const void *buf, size_t count);

#endif
