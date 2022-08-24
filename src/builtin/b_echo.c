
#include "builtin.h"

/// Необходимо обработать строки с кавычками
int exec_echo(char **cmd)
{
	int i;
	int newline;

	newline = 0;
	i = 1;
	while (cmd[i] && !ft_strncmp(cmd[i], "-n", 3))
		i++;
	if (i == 1)
		newline = 1;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	ft_free_split(cmd);
	return (0);
}