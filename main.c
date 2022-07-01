#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <readline/history.h>

#define CLOSE "\001\033[0m\002"
#define BLOD "\001\033[1m\002"
#define BEGIN(x,y) "\001\033["#x";"#y"m\002"

int main(void)
{
    char *str;
    while (1)
    {
        str = readline(BEGIN(49, 34)"Myshell $ "CLOSE);
        add_history(str);
        //Обработка
        free(str);
    }
}
