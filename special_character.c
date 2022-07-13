#include "minishell.h"

static int check_redirections(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '>' && str[stri + 1] == '>' && str[i + 2] == '>') // >>> - error; >> or > - good
		return (write(1, "redirection error\n", num_characters), 1);
	return 0;
} 

static int check_pipes(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '|' && str[i + 1] == '|') // | - good; || - not good 
		return (write(1, "pipe error\n", num_characters), 1);
	return 0;
}

int	special_character_check(char *str) // проверка на недопустимые символы
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '\"' && ft_strchr(&str[i + 1], '\"')) //ищем вхождение символа "
		{
			while (str[i] != '\"') //проматываем строку до первого вхождения данного символа
				;
		}
		else if (str[i] == '\'' && ft_strchr(&str[i + 1], '\'')) //тоже самое для '
		{
			while (str[i] != '\'') 
				;
		}
		if (str[i] == '\\' || str[i] == ';') // bonus: || и &&
		{
			write(1, "some error\n", 11)
			return (1);
		}
		if (check_pipes(&str[i]) || check_rediretions(&str[i]))
			return (1);
	}
}