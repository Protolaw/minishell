
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
			free(str);
			return (1);
		}
		if (ft_strlen(str) > 0)
			add_history(str);
		
		/// Builtins:
		if (ft_strncmp("env", str, 3) == 0) //  Проверка структуры переменных окружения
			ft_print_env(g_env);

		if (ft_strncmp("exit", str, 4) == 0) // В процессе
			exec_exit(str);    
		
		if (ft_strncmp("cd", str, 2) == 0)  //  Выполнение cd
			exec_cd(str);
		
		if (ft_strncmp("pwd", str, 3) == 0)  //  Выполнение pwd
			exec_pwd();

		if (ft_strncmp("echo", str, 4) == 0)  //  Выполнение echo
			exec_echo(str);

		if (ft_strncmp("export", str, 6) == 0)  //  Выполнение export
			exec_export(str);

		if (ft_strncmp("unset", str, 5) == 0)  //  Выполнение export
			exec_unset(str);
		//Блок обработки
		free(str);
	}
	ft_free_all();
	return (0);
}
