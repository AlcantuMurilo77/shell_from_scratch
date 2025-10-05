#include "shell.h"
#include <stdio.h>

t_builtin g_builtin[] = {

    // {.builtin_name="echo", .foo="shell_echo"},
    // {.builtin_name= "env", .foo="shell_echo"},
    {.builtin_name="exit", .foo=shell_exit}, 
    {.builtin_name=NULL}
};

void shell_exec(char **args){
    
    int i;
    const char *curr;

    i = 0;

    while((curr = g_builtin[i].builtin_name)){

        if (!strcmp(curr, args[0])){
            g_builtin[i].foo(args);
            return;
        }
        i++;
    }

    //shell_launch(args); //fork->exec

}


char *shell_read_line(void){
    char *buf;
    size_t bufsize;  
    char cwd[BUFSIZ];    

    free(buf);
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


        shell_exec(args);

        free(line);
        free(args);
    }

    return EXIT_SUCCESS;
}
