#include "minishell.h"

void    signal_processing(int signum)
{
    if (signum == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void    ft_sigaction(void)
{
    struct sigaction	s;

    memset(&s, 0, sizeof(s));
    s.sa_handler = &signal_processing; // перезаписываем действие для сигнала перерывания ctrl+c
    s.sa_flags = SA_RESTART; //позволяет некоторым системным вызовам работать, в то время как идет обработка сигналов
    sigaction(SIGINT, &s, NULL); //сигнал прерывания перезаписан выше
    sigaction(SIGQUIT, &s, NULL); //сигнал выхода ctrl+'\' более не обрабатывается
}

int main(int argc, char **argv)
{
    char    *str;
    char    **parsed;
    int     i = 0;

    parsed = NULL;
    if (argc != 1 && argv)
        return (FAILURE);
    ft_sigaction(); // https://www.opennet.ru/man.shtml?topic=sigaction&category=2&russian=0
    while (1) 
    {
        // parsed = NULL;
        // str = readline("$");
        str = readline(BEGIN(49, 34)"Minishell $ "CLOSE);
        if (!str)
            break;
        if (str[0] == '\0')
        {
            free(str);
            continue ;
        }
        parsed = ft_parse(str);

        if (parsed != NULL)
        {
            while(parsed[i])
                printf("%s\n", parsed[i++]);
        //    ft_execute(parsed, envp); 
        }
        add_history(str);
        free(str);
        free_mass(parsed);
    }
    return (0);
}
