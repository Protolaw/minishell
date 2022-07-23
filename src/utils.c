
#include "minishell.h"

int	split_count(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		i++;
	return (i);
}

int	env_add_value(char ***split, char *new_str)
{
	char	**new_split;
	int		i;

	new_split = malloc((split_count(*split) + 2) * sizeof(char *));
	if (new_split == NULL)
		return (-1);
	i = -1;
	while (*split && (*split)[++i])
		new_split[i] = (*split)[i];
	new_split[i] = new_str;
	new_split[i + 1] = NULL;
	free(*split);
	*split = new_split;
	return (0);
}

int	env_rm_value(char ***split, char *key)
{
	char	**new_split;
	int		i;

	new_split = malloc(split_count(*split) * sizeof(char *));
	if (new_split == NULL)
		return (-1);
	i = -1;
	while ((*split)[++i] != key)
		new_split[i] = (*split)[i];
	free(key);
	while ((*split)[i + 1])
	{
		new_split[i] = (*split)[i + 1];
		i++;
	}
	new_split[i] = NULL;
	free(*split);
	*split = new_split;
	return (0);
}

int	env_replace_value(char ***split, char *old_str, char *new_str)
{
	int	i;

	if (*split == NULL || old_str == NULL)
		return (-1);
	i = 0;
	while ((*split)[i] && (*split)[i] != old_str)
		i++;
	if ((*split)[i] != old_str)
		return (-1);
	free(old_str);
	(*split)[i] = new_str;
	return (0);
}

void	split_sort(char **split)
{
	char	*buf;
	int		i_strs;
	int		i;
	int		j;

	i_strs = split_count(split);
	i = -1;
	while (++i < i_strs - 1)
	{
		j = -1;
		while (++j < (i_strs - 1 - i))
		{
			if (ft_strncmp(split[j], split[j + 1], ft_strlen(split[j]) + 1) > 0)
			{
				buf = split[j];
				split[j] = split[j + 1];
				split[j + 1] = buf;
			}
		}
	}
}

