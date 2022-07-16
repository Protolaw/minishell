#include "minishell.h"

static int check_redirections(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '>' && str[stri + 1] == '>' && str[i + 2] == '>') // >>> - error; >> or > - good
		return (printf("redirection error\n"), FAILURE);
	return (SUCCESS);
} 

static int check_pipes(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '|' && str[i + 1] == '|') // | - good; || - not good 
		return (printf("pipe error\n"), FAILURE);
	return (SUCCESS);
}

int	special_character_check(char *str) // проверка на недопустимые символы
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '\"' && ft_strchr(&str[i + 1], '\"')) //ищем вхождение символа "
			while (str[++i] != '\"') //проматываем строку до первого вхождения данного символа
				;
		else if (str[i] == '\'' && ft_strchr(&str[i + 1], '\'')) //тоже самое для '
			while (str[++i] != '\'') 
				;
		if (str[i] == '\\' || str[i] == ';') // bonus: || и &&
		{
			write(1, "some error\n", 11)
			return (FAILURE);
		}
		if (check_pipes(&str[i]) || check_rediretions(&str[i]))
			return (FAILURE);
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
	if (d_q % 2 != 0 || s_q % 2 != 0)
		return (printf("error: unclosed quotes\n"), FAILURE);
	return (SUCCESS);
}