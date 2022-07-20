#include "minishell.h"

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

char	*ft_empty(char *s1) // чтобы join работал корректно строки не должны быть пусты
{
	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	return (s1);
}

static void	case_double_quotes(t_minisplit *m, char *str, char **tmp)
{
	char	*buf;

	m->i++;
	while (str[m->i] && str[m->i] != '\"')
		m->i++;
	buf = ft_substr(str, m->start, (m->i + 1));
	m->i++;
	buf = ft_empty(buf);
	tmp[m->row] = ft_empty(tmp[m->row]);
	tmp[m->row] = ft_minijoin(tmp[m->row], buf);
	m->start = m->i;
}

static void	case_single_quotes(t_minisplit *m, char *str, char **tmp)
{
	char	*buf;

	m->i++;
	while (str[m->i] && str[m->i] != '\'')
		m->i++;
	buf = ft_substr(str, m->start, (m->i + 1));
	m->i++;
	buf = ft_empty(buf);
	tmp[m->row] = ft_empty(tmp[m->row]);
	tmp[m->row] = ft_minijoin(tmp[m->row], buf);
	m->start = m->i;
}

static void	case_no_quotes(t_minisplit *m, char *str, char **tmp)
{
	int		end_sym;
	char	*buf;
  
	end_sym = 0;
	if (str[(m->i) + 1] == '\0' && str[m->i] != ' ')
		end_sym = 1;
	buf = ft_substr(str, (m->start), ((m->i) + end_sym)); // откусываем от основной строки нужный нам кусок
	m->i += end_sym;
	buf = ft_empty(buf);
	tmp[m->row] = ft_empty(tmp[m->row]);
	tmp[m->row] = ft_minijoin(tmp[m->row], buf); // после чего присоединяем его в нужную строчку в двумерном массиве
	if (str[m->i] != '\0' && str[m->i] == ' ')
		m->row++;
	while (str[m->i] && str[m->i] == ' ')
		m->i++;
	m->start = m->i;
}

static void	case_redirection(t_minisplit *m, char *str, char **tmp)
{
	//block
}

char	**ft_initialization(char **tmp, t_minisplit *m)
{
	m.i = 0;
	m.row = 0;
	m.start = 0;
	tmp = (char **)malloc(sizeof(char *) * (words_counter(str) + 1));
	if (tmp == NULL)
		exit(1);
	return (tmp);
}

char	**minishell_split(char *str) // функция разбития строки в двумерный массив строк
{
	char		**tmp;
	t_minisplit	m;

	tmp = ft_initialization(tmp, &m);
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
	tmp[m.i] = NULL;
	return (tmp);
}

char	**ft_parse(char *str)
{
	char	**tmp;

	if (quotes_check(str) || special_character_check(str)) //тут мы чекаем на неразрешенные символы и незакрытые кавычки
		return (FAILURE);
<<<<<<< HEAD
	tmp = minishell_split(str); // Предусмотреть случай если символ перенаправления ввода/вывода написан слитно с командой
}
=======
	tmp = minishell_split(str); // Предусмотреть случай если символ перенаправления ввода написан слитно с командой, в таком случае тоже требуется разделить на строки
}
>>>>>>> 63fc87fe3184ba9ffb64505010bdea1ed874a976
