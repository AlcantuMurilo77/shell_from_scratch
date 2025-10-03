#include "shell.h"
#include <stdio.h>


char *shell_read_line(void){
    char *buf;
    size_t bufsize; //what is size_t? 

    buf = NULL;

    if (getline(&buf, &bufsize, stdin) == -1){

        buf = NULL;
        if (feof(stdin)){ //why do we check for eof?
            p(RED"[EOF]"RST); //Why do we define as red and after it use rst? is it to come back to original colours?
        } else{
            p(RED"Getline failed."RST);
        }

        p("%s", buf ? buf : "((null))");; //TODO
    } //how does getline works?

    return buf;
} //why is the function a pointer?


int main(int ac, char **av){
    //Now we have to implement a REPL
    // READ->EVALUATE->PRINT/EXECUTE->LOOP

    char *line;

    while(0xCE77){ //what are we doing here with physical memory addresses?? magic numbers? what?
        // 1) get line
        // 2) get tokens (we gonna use the function gettok but ideally we should use lexing->parsing to evaluate)
        // 3) execute

        line = shell_read_line(); //TODO: Implement this function

        p("%s\n", line ? line : "((null))");p("%s\n", line);
        pause();

    }

        return EXIT_SUCCESS;
}