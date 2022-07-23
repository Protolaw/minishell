#include "minishell.h"

void	ft_scroller(char *str, char q, int *i, int *count) // промотка символов до появления закрывающей кавычки
{
	while (str[++(*i)] && str[*i] != q)
		;
	(*i)++;
	(*count)++;
}

int	words_counter(char *str) //функция подсчета требуемого количества строк для двумерного массива
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] && str[i] == '\"' && ft_strchr(&str[i + 1], '\"')) // все что находится в кавычках мы считаем за одно слово
			ft_scroller(str, '\"', &i, &count);
		else if (str[i] && str[i] == '\'' && ft_strchr(&str[i + 1], '\'')) // отдельный случай для двойных и одинарных кавычек
			ft_scroller(str, '\'', &i, &count);
		else if (str[i] && str[i] != ' ')
		{
			count++;
			while (str[i] && str[i] != ' ')
				i++;
		}
	}
	return (count);
}

/*int ft_condition(char *str, int i, int count)
{
  if (str[i] == '<' && str[i + 1] != ' ' && str[i + 1] != '<' && str[i + 1] != '\0')
    count++;
  if (str[i] == '<' && str[i - 1] != ' ' && str[i - 1] != '<' && str[0] != str[i])
    count++;
  if (str[i] == '>' && str[i + 1] != ' ' && str[i + 1] != '>' && str[i + 1] != '\0')
    count++;
  if (str[i] == '>' && str[i - 1] != ' ' && str[i - 1] != '>' && str[i - 1] != '<' && str[0] != str[i])
    count++;
  if (str[i] == '|' && str[i - 1] != ' ')
    count++;
  if (str[i] == '|' && str[i + 1] != ' ')
    count++;
  return (count);
}

int	words_counter(char *str) //функция подсчета требуемого количества строк для двумерного массива
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] && str[i] == '\"' && ft_strchr(&str[i + 1], '\"'))
			ft_scroller(str, '\"', &i, &count);
		else if (str[i] && str[i] == '\'' && ft_strchr(&str[i + 1], '\''))
			ft_scroller(str, '\'', &i, &count);
		else if (str[i] && str[i] != ' ')
		{
			count++;
			while (str[i] && str[i] != ' ')
      {
        if (str[i] == '>' || str[i] == '<' || str[i] == '|')
          count = ft_condition(str, i, count);
        i++;
      }
		}
	}
	return (count);
}*/