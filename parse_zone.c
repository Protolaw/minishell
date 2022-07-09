#include "minishell.h"

typedef struct s_minisplit
{
	int	i;
	int	row;
	int	start;
}	t_minisplit;

/*int words_counter(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '\"')
			while (str[++i] != '\"' && str[i] != '\0')
				;
		else if (str[i] == '\'')
			while (str[++i] != '\'' && str[i] != '\0')
				;
		else if (str[i] && str[i] != ' ')
		{
			count++;
			while (s[i] && s[i] != ' ')
				i++;
		}
	}
	return (count);
}*/

char	*ft_minijoin(char *s1, char *s2)
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
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (sum);
}

void	ft_empty(char *s1, char *s2)
{
	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s2)
	{
		s2 = (char *)malloc(sizeof(char) * 1);
		s2[0] = '\0';
	}
}

void	case_double_quotes(t_minisplit m, char *str, char	**tmp)
{
	char	*buf;

	m.i++;
	while (str[m.i] && str[m.i] != '\"')
		m.i++;
	buf = ft_substr(str, m.start, (m.i + 1));
	ft_empty(buf, tmp[m.row]);
	tmp[m.row] = ft_minijoin(t[m.row], buf);
	m.start = m.i;
}

void	case_single_quotes(t_minisplit m, char *str, char	**tmp)
{
	char	*buf;

	m.i++;
	while (str[m.i] && str[m.i] != '\"')
		m.i++;
	buf = ft_substr(str, m.start, (m.i + 1));
	ft_empty(buf, tmp[m.row]);
	tmp[m.row] = ft_minijoin(t[m.row], buf);
	m.start = m.i;
}

char	**minishell_split(char *str)
{
	char	*tmp;
	t_minisplit	m;

	tmp = (char **)malloc(sizeof(char *) * (words_counter(str) + 1));
	if (tmp == NULL)
		exit(1);
	while (str[m.i] == ' ')
		m.i++;
	while (str[m.i])
	{
		if (str[m.i] == '\"')
			case_double_quotes(m, str, tmp);
		else if (str[m.i] == '\'')
			case_single_quotes();
		else if (str[m.i] == ' ')
			//func
		else if (str(m.i + 1] == '\0')
			//func
		else
			i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

void	ft_parse(char *str)
{
	t_spaces	s;
	char	**tmp;

	if (special_character_check(str))
		return ;
	tmp = minishell_split(str);
}