#include "minishell.h"

int main(int argc, char **argv)
{
    char *str;
    char **env;

    env = 0;
    if (argc != 1 && argv)
        return (ft_err_print("Error: invalid argument"));
    if (ft_init_env(env) == 1)
        return (ft_err_print("Error: environment variables - not enough memory")); 
    signal(SIGQUIT, SIG_IGN); // игнорируем сигнал выхода
    // while (!exit)
    while (1)
    {
        str = readline(BEGIN(49, 34)"Myshell $ "CLOSE);
        if (str == NULL)
        {
            free(str);
            return (1);
        }
        if (ft_strlen(str) > 0)
            add_history(str);
        //Блок обработки
        free(str);
    }
    // ft_all_clear(); // чистка всего и вся
    return (0);
}
