#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>

#define INPUT_BUF 256

typedef enum { false, true }bool;

void RunEggShellPrompt();
char* CleanInputNewLine(char*);
bool ContinueInput(char*);
void ProcessUserInput(char*);

int main(int argc, char const *argv[])
{
    RunEggShellPrompt();
    return 0;
}

char* CleanInputNewLine(char* user_input){
    unsigned last_character = (unsigned)strlen(user_input)-1;
    if(user_input[last_character] == '\n')
        user_input[last_character] = '\0';
    return user_input;
}

bool ContinueInput(char* user_input){
    if (strcmp(user_input, "exit") == 0){
        return false;
    }else{
        return true;
    }
};

void ProcessUserInput(char* user_input){
    char* args[] ={"/0"};
    execv("ps",args);
}

void RunEggShellPrompt(){
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
