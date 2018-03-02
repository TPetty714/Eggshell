#include <stdio.h>
//#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#define INPUT_BUF 256

typedef enum { false, true }bool;

void RunEggShellPrompt();
char* CleanInputNewLine(char*);
bool ContinueInput(char*);
void ProcessUserInput(char*);

int main(int argc, char const *argv[]){
    RunEggShellPrompt();
    return 0;
}

char* CleanInputNewLine(char* user_input){
//  Takes user input as argument checks if the final character is a newline character
//  then changes that character to a NULL character == '\0'
    unsigned last_character = (unsigned)strlen(user_input)-1;
    if(user_input[last_character] == '\n')
        user_input[last_character] = '\0';
    return user_input;
}

bool ContinueInput(char* user_input){
//  Takes user input as argumenent, tests
//  to see if user input is equal to exit and returns false
    if (strcmp(user_input, "exit") == 0){
        return false;
    }else{
        return true;
    }
};

void ProcessUserInput(char* user_input){
//    Takes user input as argument
//    tokenizes the user input
//    tokenized arguments are then added to an array named arguments
//    The parent process forks and the child executes the arguments
//
    char* arguments [INPUT_BUF];
    char *tok = user_input;
    int arg_count = 0;
    while((tok = strtok(tok, " ")) != NULL ){
        if(strcmp(tok,"&")!=0) {
            arguments[arg_count] = tok;
            arg_count++;
        }
        tok = NULL;
    }
    arguments[arg_count] = tok;
    // once the argument is tokenized based on spaces
    // fork the process and have the parent wait.
    // child will run the command below.
    if (execvp(arguments[0], arguments)< 0){
        printf("Executable %s not Found Error: %s\n", arguments[0], strerror(errno));
    }
}

void RunEggShellPrompt(){
//    allocates memory to hold the user input.
//    Then in a do while loop the shell prompt is printed,
    int status;
    int bg;
    pid_t child_pid, wpid;
    char* user_input = malloc(sizeof(char)*INPUT_BUF);
    do{
        bg = 0;
        printf("esh$>");
        fflush(stdout);
        fflush(stdin);
        fgets(user_input, INPUT_BUF, stdin);
        user_input = CleanInputNewLine(user_input);
        if (((user_input[(int)strlen(user_input) - 1] == '&') ? 0 : 1) == 0) {
            bg = 1;
            printf("Running in background\n");
        }
        if (strcmp(user_input, "exit") != 0){
            if((child_pid = fork()) == 0){
                ProcessUserInput(user_input);
                exit(0);
            }

            else {
                if(bg == 0)
                    while((wpid = wait(&status)) <= 0);
            }
        }

    }while(ContinueInput(user_input));
    free(user_input);
}
