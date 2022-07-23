
#include "builtin.h"
#include "env.h"

int	exec_unset(char *str)
{
	int	status;
	int	i;
	int	j;
    char **split;

	split = ft_split(str, ' '); 
	if (ft_strncmp(split[0], "unset", ft_strlen(split[0])) != 0)
	{
		ft_free_split(split);
		return (-1);
	}
	status = EXIT_SUCCESS;
	i = 0;
	while (split[++i])
	{
		j = 0;
		while (split[i][j] && env_is_var_char(split[i][j]))
			j++;
		if (split[i][j] != '\0' || split[i][0] == '\0' || ft_isdigit(split[i][0]))
		{
			ft_err_print("unset", split[i], "not a valid identifier");
			status = EXIT_FAILURE;
		}
		else
			env_unset_var(split[i]);
	}
    ft_free_split(split);
	return (status);
}