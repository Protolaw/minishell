#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    char *str;

    if (argc != 1 && argv)
    {
        //error
        return (0);
    }
    signal(SIGQUIT, SIG_IGN); // игнорируем сигнал выхода 
    while (!exit)
    {
        str = readline(BEGIN(49, 34)"Myshell $ "CLOSE);
        if (str == NULL)
        {
            free(str);
            return (1)
        }
        if (ft_strlen(str) > 0)
            add_history(str);
        //Блок обработки
        free(str);
    }
    ft_all_clear(); // чистка всего и вся
    return (0);
}
