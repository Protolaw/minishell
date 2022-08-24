#include "minishell.h"

char	**g_env = NULL;

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

int	ft_exit(void *to_free, int exit_status)
{
	char	**args;

	if (exit_status == EXIT_CTRL_D)
	{
		args = ft_calloc(3, sizeof(*args));
		args[0] = ft_strdup("exit");
		// args[1] = ft_itoa(get_err_code());
		// exec_exit(args);
		ft_free_split(args);
	}
	rl_clear_history();
	free(to_free);
	ft_free_split(g_env);
	return (exit_status);
}

int ft_task(char **envp)
{
    char    *str;
    char    **parsed;
    // int     i = 0;

    parsed = NULL;
    while (1) 
    {
        str = readline(BEGIN(49, 34)"Minishell $ "CLOSE);
        if (str == NULL)
			return (ft_exit((void *)str, EXIT_CTRL_D));
        if (ft_strlen(str) > 0)
			add_history(str);
        if (str[0] == '\0')
        {
            free(str);
            continue ;
        }
        parsed = ft_parse(str);
        if (parsed != NULL)
        {
            // i = 0;
            // while(parsed[i])
			// {
            // 	// if (ft_isbuiltin(str) == 0)
			// 	// 	break;
			// 	printf("%s\n", parsed[i]);
			// 	i++;
			// }
            ft_execute(parsed, envp);
            ft_free_split(parsed);
        }
        free(str);
    }
}

int main(int argc, char **argv, char **envp)
{
    if (argc != 1 && argv)
    {
		ft_putendl_fd("Error: invalid input", 2);
		return (FAILURE);
	}
    if (ft_init_env()) //  инициализируем двумерный массив для переменных окружения
		return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
    ft_sigaction(); // https://www.opennet.ru/man.shtml?topic=sigaction&category=2&russian=0
    if (ft_task(envp) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
