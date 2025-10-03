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
int main(int ac, char **av){
    //Now we have to implement a REPL
    // READ->EVALUATE->PRINT/EXECUTE->LOOP

    char *line;

    while(0xCE77){        // 1) get line
        // 2) get tokens (we gonna use the function gettok but ideally we should use lexing->parsing to evaluate)
        // 3) execute

        line = shell_read_line(); //TODO: Implement this function

        p("%s\n", line ? line : "((null))");p("%s\n", line);
    }

        return EXIT_SUCCESS;
}