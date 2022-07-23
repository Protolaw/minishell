
#include "minishell.h"

char	**g_env = NULL;

int main(int argc, char **argv)
{
	char *str;

	if (argc > 1 && argv)
	{
		ft_putendl_fd("Error: invalid input", 2);
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
			// free(str);
			ft_free_all();
			return (1);
		}
		if (ft_strlen(str) > 0)
			add_history(str);
		
		if (ft_isbuiltin(str) == 0)
			printf("ok");
		// else
		// 	exec_cmd(str);
		//Блок обработки
		free(str);
	}
	ft_free_all();
	return (0);
}
