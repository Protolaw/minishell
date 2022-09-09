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

int	ft_exit(void *str, int exit_status)
{
	char	**exit_cmd;

	if (exit_status == EXIT_CTRL_D)
	{
		exit_cmd = ft_calloc(3, sizeof(*exit_cmd));
		exit_cmd[0] = ft_strdup("exit");
		exit_cmd[1] = ft_itoa(get_exit_status());
		exec_exit(exit_cmd);
		ft_free_split(exit_cmd);
	}
	rl_clear_history();
	if (!str)
		free(str);
	ft_free_split(g_env);
	return (exit_status);
}

int ft_task(void)
{
    char    *str;
    char    *cleaned;
    char    **parsed;

    parsed = NULL;
    while (1) 
    {
		cleaned = NULL;
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
        cleaned = ft_strtrim(str, " \t");
        if (!cleaned)
            return (FAILURE);
        parsed = ft_parse(cleaned);
        if (parsed)
        {
            ft_execute(parsed);
            ft_free_split(parsed);
        }
        free(str);
        free(cleaned);
    }
}

int main(int argc, char **argv)
{
    if (argc != 1 && argv)
    {
		ft_putendl_fd("Error: invalid input", 2);
		return (FAILURE);
	}
    if (ft_init_env()) //  инициализируем двумерный массив для переменных окружения
		return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
    ft_sigaction(); // https://www.opennet.ru/man.shtml?topic=sigaction&category=2&russian=0
    if (ft_task() == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
