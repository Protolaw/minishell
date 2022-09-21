#include "minishell.h"

int	case_double_quotes(t_minisplit *m, char *str, char **tmp)
{
	char	*buf;

	m->i++;
	while (str[m->i] && str[m->i] != '\"')
		m->i++;
	buf = ft_minisubstr(str, m->start, (m->i + 1));
	if (!buf)
		return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
	m->i++;
	buf = ft_empty(buf);
	if (!buf)
		return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
	tmp[m->row] = ft_empty(tmp[m->row]);
	if (!tmp[m->row])
		return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
	tmp[m->row] = ft_minijoin(tmp[m->row], buf);
	m->start = m->i;
	return (0);
}

int	case_single_quotes(t_minisplit *m, char *str, char **tmp)
{
	char	*buf;

	m->i++;
	while (str[m->i] && str[m->i] != '\'')
		m->i++;
	buf = ft_minisubstr(str, m->start, (m->i + 1));
	m->i++;
	buf = ft_empty(buf);
	if (!buf)
		return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
	tmp[m->row] = ft_empty(tmp[m->row]);
	tmp[m->row] = ft_minijoin(tmp[m->row], buf);
	if (!tmp[m->row])
		return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
	m->start = m->i;
	return (0);
}

int	case_no_quotes(t_minisplit *m, char *str, char **tmp)
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
	if (!buf)
		return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
	tmp[m->row] = ft_empty(tmp[m->row]);
	tmp[m->row] = ft_minijoin(tmp[m->row], buf); // после чего присоединяем его в нужную строчку в двумерном массиве
	if (!tmp[m->row])
		return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
	if (str[m->i] != '\0' && str[m->i] == ' ')
		m->row++;
	while (str[m->i] && str[m->i] == ' ')
		m->i++;
	m->start = m->i;
	return (0);
}

int red_no_space(char *str, t_minisplit *m, char **tmp)
{
    char *buf;

    buf = ft_minisubstr(str, m->start, (m->i));
    buf = ft_empty(buf);
    if (!buf)
        return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
    tmp[m->row] = ft_empty(tmp[m->row]);
    tmp[m->row] = ft_minijoin(tmp[m->row], buf);
    if (!tmp[m->row])
        return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
    m->row++;
    m->start = m->i;
    return (0);
}

int case_redirection(t_minisplit *m, char *str, char **tmp)
{
	char *buf;
	char red;

	red = str[m->i];
	if (str[m->i - 1] != ' ') 
		if (red_no_space(str, m, tmp))
            return (-1);
	while (str[++m->i] && str[m->i] == red)
		;
	buf = ft_minisubstr(str, m->start, (m->i));
	buf = ft_empty(buf);
	if (!buf)
		return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
	tmp[m->row] = ft_empty(tmp[m->row]);
	tmp[m->row] = ft_minijoin(tmp[m->row], buf);
	if (!tmp[m->row])
		return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
	m->row++;
	while (str[m->i] && str[m->i] == ' ')
		m->i++;
	m->start = m->i;
	return (0);
}