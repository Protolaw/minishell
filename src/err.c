
# include "../inc/minishell.h"

int	ft_err_print(char *s1, char *s2, char *err_log)
{
	ft_putstr_fd(SHELL_NAME, 2);
	if (s1)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(s1, 2);
	}
	if (s2)
	{
		if (s1)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(s2, 2);
	}
	if (err_log)
	{
		if (s1 || s2)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(err_log, 2);
	}
	ft_putchar_fd('\n', 2);
	return (-1);
}

int	print_err_errno(char *s1, char *s2)
{
	ft_err_print(s1, s2, strerror(errno));
	errno = 0;
	return (-1);
}