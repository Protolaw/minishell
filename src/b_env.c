
#include "../inc/builtin.h"

// Печать переменных окружения

int	ft_print_env(char **env)
{
	int	i;

	if (env == NULL)
		return (ft_err_print("env", NULL, "environ not set"));
	i = 0;
	while (env[i])
		ft_putendl_fd(env[i++], 1);
	return (0);
}