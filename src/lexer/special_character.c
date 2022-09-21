#include "lexer.h"

static int	check_red_condition(char *s)
{
	if (s[0] == '\0')
		return (ft_newline_error());
	else if ((s[0] == '<' && s[1] == '<') 
		|| (s[0] == '>' && s[1] == '>'))
		return (ft_syntax_error(2, s[0]));
	else if (s[0] == '<' || s[0] == '>')
		return (ft_syntax_error(1, s[0]));
	else
		return (SUCCESS);
}

static int check_red_left(char *str, int *i)
{
	if (str[*i] == '<') 
	{
		if (str[++(*i)] == '<' && str[*i + 1] != ' ')
			return (check_red_condition(&str[++(*i)]));
		else if (str[*i] == '>' && str[(*i) + 1] != ' ')
			return (check_red_condition(&str[++(*i)]));
		else if (str[*i] != '<' && str[*i] != '>' && str[*i] != ' ')
			return (check_red_condition(&str[*i]));
		if (str[*i] == '<')
			(*i)++;
		while (str[++(*i)] && str[*i] == ' ')
			;
		return (check_red_condition(&str[*i]));
	}
	return (SUCCESS);
}

static int check_red_right(char *str, int *i)
{
	if (str[*i] == '>')
	{
		if (str[++(*i)] == '>' && str[*i + 1] != ' ')
			return (check_red_condition(&str[++(*i)]));
		else if (str[*i] != '>' && str[*i] != ' ')
			return (check_red_condition(&str[*i]));
		if (str[*i] == '>')
			(*i)++;
		while (str[++(*i)] && str[*i] == ' ')
			;
		return (check_red_condition(&str[*i]));
	}
	return (SUCCESS);
}

int	special_character_check(char *str) // проверка на недопустимые символы
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' && ft_strchr(&str[i + 1], '\"'))
			while (str[++i] != '\"')
				;
		else if (str[i] == '\'' && ft_strchr(&str[i + 1], '\''))
			while (str[++i] != '\'') 
				;
		if (str[i] == '\\' || str[i] == ';') // bonus: || и &&
			return (ft_syntax_error(1, str[i]));
		if (check_red_left(str, &i) || check_red_right(str, &i) || check_pipes(str, &i))
			return (FAILURE);
		else 
			i++;
	}
	return (SUCCESS);
}

int	quotes_check(char *str) // проверяем на незыкрытые кавычки 
{
	int	s_q;
	int	d_q;
	int i;

	i = 0;
	s_q = 0;
	d_q = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
			d_q = quotes_counter(str, &i, d_q, '\"');
		else if (str[i] == '\'')
			s_q = quotes_counter(str, &i, s_q, '\'');
		i++;
	}
	return (ft_quotes_error(d_q, s_q));
}
