
#include "../inc/minishell.h"

char	**g_env = NULL;

int main(int argc, char **argv)
{
    char *str;

    if (argc != 1 && argv)
    {
        ft_putendl_fd("Error: invalid argument", 2);
        return (1);
    }
    if (ft_init_env()) //  инициализируем двумерный массив для переменных окружения
        return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
    signal(SIGQUIT, SIG_IGN); // игнорируем сигнал выхода
    while (1)
    {
        str = readline(BEGIN(49, 34)"minishell $ "CLOSE);
        if (str == NULL)
        {
            free(str);
            return (1);
        }
        if (ft_strlen(str) > 0)
            add_history(str);
        
        if (ft_strncmp("env", str, 3) == 0) //  Проверка структуры переменных окружения
            ft_print_env(g_env);

        if (ft_strncmp("exit", str, 4) == 0) // В процессе
            exit(1);    //  Сюда билт-ин
        
        if (ft_strncmp("cd", str, 2) == 0)  //  Выполнение cd
            exec_cd(str);
            

        //Блок обработки
        free(str);
    }
    ft_free_all();
    return (0);
}
