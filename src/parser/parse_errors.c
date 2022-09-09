#include "minishell.h"

int	ft_newline_error(void)
{
	ft_err_print(NULL, NULL, "syntax error near unexpected token 'newline'\n");
	return (FAILURE);
}

int	ft_syntax_error(int d, char c)
{
	if (d == 1)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": syntax error near unexpected token `", 2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd("'\n", 2);
	}
	else if (d == 2)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": syntax error near unexpected token `", 2);
		ft_putchar_fd(c, 2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd("'\n", 2);
	}
	set_exit_status(2);
	return (FAILURE);
}

int	ft_quotes_error(int d_q, int s_q)
{
	if (d_q % 2 != 0)
		return (ft_syntax_error(1, '\"'));
	else if (s_q % 2 != 0)
		return (ft_syntax_error(1, '\''));	
	else
		return (SUCCESS);
}