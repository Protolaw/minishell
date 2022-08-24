
#include "builtin.h"

int ft_isbuiltin(char **cmd)
{
	if (ft_strncmp("env", cmd[0], 3) == 0 && ft_strlen(cmd[0]) == 3)
		return (ft_print_env(g_env));
	if (ft_strncmp("exit", cmd[0], 4) == 0 && ft_strlen(cmd[0]) == 4)
		return (exec_exit(cmd));    
	if (ft_strncmp("cd", cmd[0], 2) == 0 && ft_strlen(cmd[0]) == 2)
		return (exec_cd(cmd));
	if (ft_strncmp("pwd", cmd[0], 3) == 0 && ft_strlen(cmd[0]) == 3)
		return (exec_pwd());
	if (ft_strncmp("echo", cmd[0], 4) == 0 && ft_strlen(cmd[0]) == 4)
		return (exec_echo(cmd));
	if (ft_strncmp("export", cmd[0], 6) == 0 && ft_strlen(cmd[0]) == 6)
		return (exec_export(cmd));
	if (ft_strncmp("unset", cmd[0], 5) == 0 && ft_strlen(cmd[0]) == 5) 
		return (exec_unset(cmd));
	else
		return (1);
}