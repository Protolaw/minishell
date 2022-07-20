#include "minishell.h"

int	ft_newline_error(void)
{
	printf("syntax error near unexpected token `newline'\n");
	return (FAILURE);
}

int	ft_syntax_error(int d, char c)
{
	if (d == 1)
		printf("syntax error near unexpected token `%c'\n", c);
	else if (d == 2)
		printf("syntax error near unexpected token `%c%c'\n", c, c);
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