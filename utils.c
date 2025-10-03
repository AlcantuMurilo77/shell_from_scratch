#include "shell.h"
#include <stddef.h>
//Wrappers

void *Getcwd(char *buf, size_t size){

    if (NULL == getcwd(buf, size)){
        perror(RED"getcwd failed"RST); 
    }


}
