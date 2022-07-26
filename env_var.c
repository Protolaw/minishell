#include "minishell.h"

// в разработке

int	check_sym(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '$' && s[1] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
char	**environment_variables(char **tmp)
{
	int		i;
	int		j;
	char	**env;
	char	*str;

	i = 0;
	j = 0;
	str = NULL;
	env = (char **)malloc(sizeof(char *) * (strlen_mass(tmp) + 1))
	if (!env)
		exit (1);
	while (tmp[i])
	{
		if (check_sym(&tmp[i]))
		{
			str = 
		}
		else 
		{

		}
		i++;
	}
}