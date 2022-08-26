#include "minishell.h"

char	*str_append(char *s1, char *s2)
{
	char	*buf;

	buf = s1;
	s1 = ft_strjoin(s1, s2);
	free(buf);
	return (s1);
}