
#include "builtin.h"

int ft_isbuiltin(char *str)
{
	if (ft_strncmp("env", str, 3) == 0) //  Проверка структуры переменных окружения
		return (ft_print_env(g_env));
	if (ft_strncmp("exit", str, 4) == 0) // В процессе
		return (exec_exit(str));    
	if (ft_strncmp("cd", str, 2) == 0)  //  Выполнение cd
		return (exec_cd(str));
	if (ft_strncmp("pwd", str, 3) == 0)  //  Выполнение pwd
		return (exec_pwd());
	if (ft_strncmp("echo", str, 4) == 0)  //  Выполнение echo
		return (exec_echo(str));
	if (ft_strncmp("export", str, 6) == 0)  //  Выполнение export
		return (exec_export(str));
	if (ft_strncmp("unset", str, 5) == 0)  //  Выполнение export
		return (exec_unset(str));
	else
		return (0);
}