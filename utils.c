#include "shell.h"
#include <sys/wait.h>

//Wrappers

void *Getcwd(char *buf, size_t size){

    if (NULL == getcwd(buf, size)){
        perror(RED"getcwd failed"RST); 
    }


}


void *Malloc(size_t size){

    void *ptr;

    if (size == 0){
        return (NULL);
    }
    ptr = malloc(size);
    if (!ptr){
        perror(RED"Malloc failed"RST);
        exit(EXIT_FAILURE);
    }
    return (ptr);


}

void *Realloc(void *ptr, size_t size){

    void *new_ptr;

    new_ptr = realloc(ptr, size);
    if (!new_ptr && size != 0){
        perror(RED"Realloc failed"RST);
        exit(EXIT_FAILURE);
    }
    return (new_ptr);

}

pid_t Fork(void){
    pid_t pid;

    pid = fork();
    if (pid < 0){
        perror(RED"Fork failed" RST);
        exit(EX_OSERR);
    }
    return (pid);
}

void Execvp(const char *file, char *const argv[]){

    if (!file || !argv){
        fprintf(stderr, RED"Execvp: invalid arguments\n"RST);
        exit(EXIT_FAILURE);
    }
    if (execvp(file, argv) == -1){
        perror(RED"Child process failed"RST);
        exit(EX_UNAVAILABLE );
    }
}

pid_t Wait(int *status){
    
    pid_t result;

    if (!status){
        fprintf(stderr, RED"Wait: status argument required\n"RST);
        return (-1);
    }
    result = wait(status);
    if (result == -1){
        perror(RED"Wait failed"RST);
    }

    if(WIFEXITED(*status)){
        *status = WEXITSTATUS(*status);
    }

    return (result);
}
