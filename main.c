#include <stdio.h>

#define INPUT_BUF 256

typedef enum { false, true } bool;

void ReadUserInput();
char* CleanInputNewLine(char*);
bool ContinueInput(char*);

int main(int argc, char const *argv[])
{
    ReadUserInput();
    return 0;
}


void ReadUserInput(){
    char* user_input = malloc(sizeof(char)*INPUT_BUF);
    do{
        printf("esh$>");
        fflush(stdin);
        fgets(user_input, INPUT_BUF, stdin);
        user_input = CleanInputNewLine(user_input);
        ProcessUserInput();
    }while(ContinueInput(user_input));
    free(user_input);
}
