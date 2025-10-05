#ifndef SHELL_H
#define SHELL_H
#define SHELL_CHILD 0 

#include <stddef.h>
#include <sys/types.h>
#include <unistd.h>
#include <sysexits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#define Y "\033[1;33m"
#define G "\033[1;32m"
#define C "\033[1;36m"
#define RED "\033[1;31m"
#define RST "\033[0m"

#define p(...) printf(__VA_ARGS__) 
#define DEL "\n\t \v\f\r"

typedef struct c_builtin{

    const char *builtin_name;
    int (*foo)(char **args);
} t_builtin;


pid_t Wait(int *status);
pid_t Fork(void); 
void Execvp(const char *file, char *const argv[]);
int shell_exit(char **args);
void *Getcwd(char *buf, size_t size);
void *Malloc(size_t size);
void *Realloc(void *ptr, size_t size);
#endif
