
#include "builtin.h"
#include "env.h"

int	exec_unset(char **cmd)
{
	int	status;
	int	i;
	int	j;

	status = EXIT_SUCCESS;
	i = 0;
	while (cmd[++i])
	{
		j = 0;
		while (cmd[i][j] && env_is_var_char(cmd[i][j]))
			j++;
		if (cmd[i][j] != '\0' || cmd[i][0] == '\0' || ft_isdigit(cmd[i][0]))
		{
			ft_err_print("unset", cmd[i], "not a valid identifier");
			status = EXIT_FAILURE;
		}
		else
			env_unset_var(cmd[i]);
	}
    ft_free_split(cmd);
	return (status);
}