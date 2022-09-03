#include "minishell.h"

char	*str_append(char *s1, char *s2)
{
	char	*buf;

	buf = s1;
	s1 = ft_strjoin(s1, s2);
	free(buf);
	return (s1);
}

char	*chr_append(char *str, char chr)
{
	char	*new_str;
	int		i;

	if (str == NULL)
		return (NULL);
	new_str = malloc(ft_strlen(str) + 2);
	if (new_str != NULL)
	{
		i = 0;
		while (str[i])
		{
			new_str[i] = str[i];
			i++;
		}
		new_str[i] = chr;
		new_str[i + 1] = '\0';
	}
	free(str);
	return (new_str);
}

int	split_replace_str(char ***split, char *old_str, char *new_str)
{
	int	i;

	if (*split == NULL || old_str == NULL)
		return (FAILURE);
	i = 0;
	while ((*split)[i] && (*split)[i] != old_str)
		i++;
	if ((*split)[i] != old_str)
		return (FAILURE);
	free(old_str);
	(*split)[i] = new_str;
	return (0);
}