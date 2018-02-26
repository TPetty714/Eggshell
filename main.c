#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define INPUT_BUF 256

typedef enum { false, true }bool;

void ReadUserInput();
char* CleanInputNewLine(char*);
bool ContinueInput(char*);

int main(int argc, char const *argv[])
{
    ReadUserInput();
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

void ReadUserInput(){
    char* user_input = malloc(sizeof(char)*INPUT_BUF);
    do{
        printf("esh$>");
        fflush(stdin);
        fgets(user_input, INPUT_BUF, stdin);
         user_input = CleanInputNewLine(user_input);
        // ProcessUserInput();
    }while(ContinueInput(user_input));
    free(user_input);
}
