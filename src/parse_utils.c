#include "minishell.h"

void	ft_scroller(char *str, char q, int *i, int *count) // промотка символов до появления закрывающей кавычки
{
	while (str[++(*i)] && str[*i] != q)
		;
	(*i)++;
	(*count)++;
}

char	*ft_minijoin(char *s1, char *s2) // как обычный join только + еще чистит память за собой
{
	size_t	i;
	size_t	j;
	char	*sum;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	sum = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!sum)
		return (NULL);
	if (s1)
		while (s1[++i] != '\0')
			sum[i] = s1[i];
	while (s2[j] != '\0')
		sum[i++] = s2[j++];
	sum[i] = '\0';
	free(s1);
	free(s2);
	return (sum);
}

/*int	words_counter(char *str) //функция подсчета требуемого количества строк для двумерного массива
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
}*/

static void ft_condition(char *str, int i, int *count)
{
	if (str[i] == '<' && str[i + 1] != ' ' && str[i + 1] != '<' && str[i + 1] != '\0')
		(*count)++;
	if (str[i] == '<' && str[i - 1] != ' ' && str[i - 1] != '<' && str[0] != str[i])
		(*count)++;
	if (str[i] == '>' && str[i + 1] != ' ' && str[i + 1] != '>' && str[i + 1] != '\0')
		(*count)++;
	if (str[i] == '>' && str[i - 1] != ' ' && str[i - 1] != '>' && str[i - 1] != '<' && str[0] != str[i])
		(*count)++;
	if (str[i] == '|' && str[i - 1] != ' ')
		(*count)++;
	if (str[i] == '|' && str[i + 1] != ' ')
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
          			ft_condition(str, i, &count);
        		i++;
      		}
		}
	}
	return (count);
}

void	**free_mass(char **mass)
{
	int	i;

	i = 0;
	if (mass == NULL)
		return ;
	while (mass[i])
	{
		free(mass[i]);
		i++;
	}
	free(mass);
	mass = NULL;
}