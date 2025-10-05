#include "shell.h"
#include <stddef.h>
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