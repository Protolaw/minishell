#include "minishell.h"

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

static void case_redirection(t_minisplit *m, char *str, char **tmp) 
{
	char *buf;
	char red;

	red = str[m->i];
	if (str[m->i - 1] != ' ') 
	{
		buf = ft_substr(str, m->start, (m->i));
		buf = ft_empty(buf);
		tmp[m->row] = ft_empty(tmp[m->row]);
		tmp[m->row] = ft_minijoin(tmp[m->row], buf);
		m->row++;
		m->start = m->i;
	}
	while (str[++m->i] && str[m->i] == red)
		;
	buf = ft_substr(str, m->start, (m->i));
	buf = ft_empty(buf);
	tmp[m->row] = ft_empty(tmp[m->row]);
	tmp[m->row] = ft_minijoin(tmp[m->row], buf);
	m->row++;
	while (str[m->i] && str[m->i] == ' ')
		m->i++;
	m->start = m->i;
}

char	**ft_initialization(char *str, char **tmp, t_minisplit *m)
{
	m->i = 0;
	m->row = 0;
	m->start = 0;
	tmp = (char **)malloc(sizeof(char *) * (words_counter(str) + 1));
	//printf("%d\n", words_counter(str));
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

char	**ft_parse(char *str, char **envp)
{
	char	**tmp;
	char	**env;

	(void)*envp;
	if (quotes_check(str) || special_character_check(str)) //тут мы чекаем на неразрешенные символы и незакрытые кавычки
		return (NULL);
	tmp = minishell_split(str); // парсинг с учетом кавычек и перенаправлений
	//env = environment_variables(tmp, envp); тут пока хз, не получается без мака норм затестить
	//free_mass(tmp);
	env = remove_quotes(tmp);
	return (env);
}
