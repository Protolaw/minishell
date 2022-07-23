
#include "builtin.h"

/// Необходимо обработать строки с кавычками
int exec_echo(char *str)
{
	char **split;
	int i;
	int newline;

	newline = 0;
	split = ft_split(str, ' '); 
	i = 1;
	while (split[i] && !ft_strncmp(split[i], "-n", 3))
		i++;
	if (i == 1)
		newline = 1;
	while (split[i])
	{
		ft_putstr_fd(split[i], 1);
		if (split[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	ft_free_split(split);
	return (0);
}