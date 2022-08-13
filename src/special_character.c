#include "minishell.h"

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

static int check_pipes(char *str, int *i)
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

static int	quotes_counter(char *str, int *i, int count, char quote)
{
	count++;
	(*i)++;
	while(str[(*i)] != quote && str[(*i)] != '\0')
		(*i)++;
	if (str[(*i)] == quote)
		count++;
	return (count);
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

int is_valid_str(char *str, int i)
{
	while (i > 0 && str[i] && ft_isspace(str[i]))
		i--;
	if (i >= 0 && (str[i] != '&' && str[i] != '|'))
		return (0);
	return (1);
}

int	has_opening_bracket(char *line, int i)
{
	while (i > 0 && line[i] && line[i] != '(')
		i--;
	if (i >= 0 && line[i] != '(')
		return (0);
	return (1);
}

int	count_chars(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{		
		if (str[i] == '\'')
			while (str[i] && str[i+1] != '\'')
				i++;
		if (str[i] == '\"')
			while (str[i] && str[i+1] != '\"')
				i++;
		if (str[i] == c)
			count++;
		if (str[i])
			i++;
	}
	return (count);
}

int brackets_check(char *str)
{
	int i;

	i = 0;
	if (count_chars(str, '(') != count_chars(str, ')'))// Чекаем количество открытых и закрытых скобок
		return (ft_syntax_error(1, '(')); // Exit_status
	while (str[i])
	{
		if (str[i] == '(')
			if (!is_valid_str(str, i - 1))
				return (ft_syntax_error(1, '('));
		if (str[i] == ')')
			if (!has_opening_bracket(str, i - 1))
				return (ft_syntax_error(1, '('));
		if (str[i])
			i++;
	}
	return (0);
}
