#include "minishell.h"

char *ft_minisubstr(char *s, int start, int len) 
{
	char *tab;
	int i;
	int j;

	tab = NULL;
	if (s == 0)
		return (0);
	if (len >= (int)ft_strlen(s))
		tab = malloc(sizeof(char) * (ft_strlen(s) + 1));
	else if (len < (int)ft_strlen(s))
		tab = malloc(sizeof(char) * (len + 1));
	if (tab == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i] != '\0')
		if (i >= start && i < len)
			tab[j++] = s[i];
	tab[j] = '\0';
	return (tab);
}

char	**ft_initialization(char *str, char **tmp, t_minisplit *m)
{
	m->i = 0;
	m->row = 0;
	m->start = 0;
	tmp = ft_calloc((words_counter(str) + 1), sizeof(char *)); // Решил выделять память так с заполнением 0
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

char	**minishell_split(char *str, char **tmp,t_minisplit m) // функция разбития строки в двумерный массив строк
{
	while (str[m.i] == ' ')
		m.i++;
	while (str[m.i])
	{
		if (str[m.i] == '\"')
			case_double_quotes(&m, str, tmp);
		else if (str[m.i] == '\'')
			case_single_quotes(&m, str, tmp);
		else if (str[m.i] == ' ' || str[m.i + 1] == '\0')
			case_no_quotes(&m, str, tmp);
		else if (str[m.i] == '>' || str[m.i] == '<' || str[m.i] == '|')
			case_redirection(&m, str, tmp);
		else
			m.i++;
	}
	tmp[++m.row] = NULL;
	return (tmp);
}

char	**ft_parse(char *str)
{
	char	**tmp;
	t_minisplit	m;

	tmp = NULL;
	if (quotes_check(str) || special_character_check(str))
	{
		set_exit_status(2);
		return (NULL);
	}
	tmp = ft_initialization(str, tmp, &m);
	if (!tmp)
		return (NULL);
	tmp = minishell_split(str, tmp, m); 
	if (!tmp)
		return (NULL);
	tmp = remove_quotes(tmp);
	return (tmp);
}
