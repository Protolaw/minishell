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
		return (0);
	i = 0;
	j = 0;
	while (s[i] != '\0') 
	{
		if (i >= start && i < len)
			tab[j++] = s[i];
		i++;
  	}
	tab[j] = '\0';
	return (tab);
}

void	case_double_quotes(t_minisplit *m, char *str, char **tmp)
{
	char	*buf;

	m->i++;
	while (str[m->i] && str[m->i] != '\"')
		m->i++;
	buf = ft_minisubstr(str, m->start, (m->i + 1));
	m->i++;
	buf = ft_empty(buf);
	tmp[m->row] = ft_empty(tmp[m->row]);
	tmp[m->row] = ft_minijoin(tmp[m->row], buf);
	m->start = m->i;
}

void	case_single_quotes(t_minisplit *m, char *str, char **tmp)
{
	char	*buf;

	m->i++;
	while (str[m->i] && str[m->i] != '\'')
		m->i++;
	buf = ft_minisubstr(str, m->start, (m->i + 1));
	m->i++;
	buf = ft_empty(buf);
	tmp[m->row] = ft_empty(tmp[m->row]);
	tmp[m->row] = ft_minijoin(tmp[m->row], buf);
	m->start = m->i;
}

void	case_no_quotes(t_minisplit *m, char *str, char **tmp)
{
	int		end_sym;
	char	*buf;
  
	end_sym = 0;
	buf = NULL;
	if (str[(m->i) + 1] == '\0' && str[m->i] != ' ')
		end_sym = 1;
	buf = ft_minisubstr(str, (m->start), ((m->i) + end_sym)); // откусываем от основной строки нужный нам кусок
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

void case_redirection(t_minisplit *m, char *str, char **tmp) 
{
	char *buf;
	char red;

	red = str[m->i];
	if (str[m->i - 1] != ' ') 
	{
		buf = ft_minisubstr(str, m->start, (m->i));
		buf = ft_empty(buf);
		tmp[m->row] = ft_empty(tmp[m->row]);
		tmp[m->row] = ft_minijoin(tmp[m->row], buf);
		m->row++;
		m->start = m->i;
	}
	while (str[++m->i] && str[m->i] == red)
		;
	buf = ft_minisubstr(str, m->start, (m->i));
	buf = ft_empty(buf);
	tmp[m->row] = ft_empty(tmp[m->row]);
	tmp[m->row] = ft_minijoin(tmp[m->row], buf);
	m->row++;
	while (str[m->i] && str[m->i] == ' ')
		m->i++;
	m->start = m->i;
}

static char	**ft_initialization(char *str, char **tmp, t_minisplit *m)
{
	m->i = 0;
	m->row = 0;
	m->start = 0;
	tmp = ft_calloc((words_counter(str) + 1), sizeof(char *)); // Решил выделять память так с заполнением 0
	// tmp = (char **)malloc(sizeof(char *) * (words_counter(str) + 10));
	if (tmp == NULL)
		exit(1);
	return (tmp);
}

char	**minishell_split(char *str) // функция разбития строки в двумерный массив строк
{
	char		**tmp;
	t_minisplit	m;

	tmp = NULL;
	tmp = ft_initialization(str, tmp, &m);
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

	tmp = NULL;
	if (quotes_check(str) || special_character_check(str) || brackets_check(str)) //Чекаем на неразрешенные символы и незакрытые кавычки и скобки
		return (NULL); // Exit_status
	tmp = minishell_split(str); // парсинг с учетом кавычек и перенаправлений
	//env = environment_variables(tmp, envp); тут пока хз, не получается без мака норм затестить
	// tmp = remove_quotes(tmp);
	return (tmp);
}
