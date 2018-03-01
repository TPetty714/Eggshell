#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

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
        arguments[arg_count] = tok;
        tok = NULL;
        arg_count++;
    }
    arguments[arg_count] = tok;
    // once the argument is tokenized based on spaces
    // fork the process and have the parent wait.
    // child will run the command below.
    if (execvp(arguments[0], arguments)< 0){
        printf("Executable not Found Error: %s\n", strerror(errno));
    }
}

void RunEggShellPrompt(){
//    allocates memory to hold the user input.
//    Then in a do while loop the shell prompt is printed,
//
    char* user_input = malloc(sizeof(char)*INPUT_BUF);
    do{
        printf("esh$>");
        fflush(stdin);
        fgets(user_input, INPUT_BUF, stdin);
        user_input = CleanInputNewLine(user_input);
        ProcessUserInput(user_input);
    }while(ContinueInput(user_input));
    free(user_input);
}
