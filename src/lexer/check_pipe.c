#include "lexer.h"

static int check_pipe_back(char *s, int *i)
{
	int  len;

	len = (*i);
	while (--len >= 0)
		if (s[len] != '\0' && s[len] != ' '
			&& s[len] != '<' && s[len] != '>')
			return (SUCCESS);
	return (ft_syntax_error(1, '|'));
}

static int  check_pipe_newline(char *s, int *i)
{
	while (s[++(*i)] && s[*i] == ' ')
		;
	if (s[*i] == '|')
		return (ft_syntax_error(1, '|'));
	if (s[*i] != '\0')
		return (SUCCESS);
	return (ft_newline_error());
}

int check_pipes(char *str, int *i)
{
	if(str[*i] == '|')
	{
		if (str[*i] == '|' && str[(*i) + 1] == '|') 
			return (ft_syntax_error(2, '|'));
		else if (str[*i] == '|' && str[(*i) + 1] == '\0')
			return (ft_syntax_error(1, '|'));
		else if (check_pipe_back(str, i) || check_pipe_newline(str, i))
			return (FAILURE);
	}
	return (SUCCESS);
}

int	quotes_counter(char *str, int *i, int count, char quote)
{
	count++;
	(*i)++;
	while(str[(*i)] != quote && str[(*i)] != '\0')
		(*i)++;
	if (str[(*i)] == quote)
		count++;
	return (count);
}
