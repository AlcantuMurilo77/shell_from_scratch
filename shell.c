#include "shell.h"
#include <stdio.h>


char *shell_read_line(void){
    char *buf;
    size_t bufsize;  
    char cwd[BUFSIZ];    


    buf = NULL;

    Getcwd(cwd, sizeof(cwd));

    p(C"%s  $>"RST, cwd);

    if (getline(&buf, &bufsize, stdin) == -1){

        buf = NULL;
        if (feof(stdin)){ 
            p(RED"[EOF]"RST);
        } else{
            p(RED"Getline failed."RST);
        }

        p("%s", buf ? buf : "((null))");; //TODO
    } 

    return buf;
} 

char **shell_split_line(char *line){

    char **tokens;
    unsigned int position;
    size_t bufsize;

    bufsize = BUFSIZ;
    tokens = Malloc(bufsize * sizeof(*tokens));
    position = 0;

    for (char *token = strtok(line, DEL); token; token = strtok(NULL, DEL)){
        tokens[position++] = token;
        if (position >= bufsize){

            bufsize *= 2;
            tokens = Realloc(tokens, bufsize * sizeof(*tokens));


        }

    }
    tokens[position] == NULL;

    return tokens;

}





int main(int ac, char **av){
    //Now we have to implement a REPL
    // READ->EVALUATE->PRINT/EXECUTE->LOOP

    char *line;
    char **args;


    while(line = shell_read_line()){                
        
        args = shell_split_line(line);

        for(int i =0; args[i]; i++){
            p("%s\n", args[i]);
        }

    }

        return EXIT_SUCCESS;
}