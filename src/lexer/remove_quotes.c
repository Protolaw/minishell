#include "minishell.h"

int	check_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

static void	case_quotes(char *new, char *s, char quote, int *i, int *j)
{
	(*i)++;
	while (s[*i] != '\0' && s[*i] != quote)
		new[(*j)++] = s[(*i)++];
	(*i)++; 
}

static char *check_new(char *new)
{
	if (new[0] == '\0')
	{
		free (new);
		new = NULL;
	}
	return (new);
}

char	*no_quotes(char *s)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * ((int)ft_strlen(s) - 1));
	if (!new)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
			case_quotes(new, s, s[i], &i, &j);
		else
			new[j++] = s[i++];
	}
	new[j] = '\0';
	free (s);
	return (check_new(new));
}

// char	**remove_quotes(char **argv)
// {
	// int	i;
	// char **new_argv;
	// int j;

	// i = 0;
	// j = 0;
	// new_argv = ft_calloc((split_count(argv) + 1), sizeof(char *));
	// if (new_argv == NULL)
	// 	return (NULL);
	// while (argv[i])
	// {
	// 	if (check_quotes(argv[i]))
	// 	{
	// 		argv[i] = no_quotes(argv[i]);
	// 		if (argv[i] != NULL)
	// 			new_argv[j] = ft_strdup(argv[i]);
	// 		else
	// 			j--;
	// 	}
	// 	else
	// 		new_argv[j] = ft_strdup(argv[i]);
	// 	free(argv[i]);
	// 	j++;
	// 	i++;
	// }
	// new_argv[j] = NULL;
	// free(argv);
// 	return (new_argv);
// }

char	**remove_quotes(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (check_quotes(argv[i]))
			argv[i] = no_quotes(argv[i]);
		i++;
	}
	return (argv);
}