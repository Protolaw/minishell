
#include "builtin.h"
#include "env.h"

void	print_vars(void)
{
	char	**env_copy;
	int		l_var_name;
	int		i;

	if (g_env == NULL || *g_env == NULL)
		return ;
	env_copy = malloc((split_count(g_env) + 1) * sizeof(char *));
	if (env_copy == NULL)
	{
		ft_err_print(NULL, NULL, strerror(ENOMEM));
		return ;
	}
	env_copy = ft_memcpy(env_copy, g_env,
			(split_count(g_env) + 1) * sizeof(char *));
	split_sort(env_copy);
	i = -1;
	while (env_copy[++i])
	{
		l_var_name = ft_strchr(env_copy[i], '=') - env_copy[i];
		printf("declare -x ");
		printf("%.*s", l_var_name + 1, env_copy[i]);
		printf("\"%s\"\n", get_value_env(env_copy[i]));
	}
	free(env_copy);
}

int is_valid_argument(char *arg)
{
	int	i;

	if (arg[0] == '\0' || arg[0] == '=')
		return (0);
	i = 0;
	while (arg[i] != '\0' && arg[i] != '=' && env_is_var_char(arg[i]))
		i++;
	if (arg[i] == '\0' || arg[i] == '=')
		return (1);
	else
		return (0);
}

int handle_export(char **split, int j)
{
	int i;

	i = 1;
	while (j > 1 && split[i])
	{
		if (is_valid_argument(split[i]) == 0 || ft_isdigit(split[i][0]))
		{
			ft_err_print("export", split[i], "not a valid identifier");
			return (1);
		}
		else if (ft_strchr(split[i], '='))
			env_put_var(split[i]);
		i++;
	}
	return (0);
}

int	exec_export(char *str)
{
	int	status;
	char **split;
	int j;

	split = ft_split(str, ' '); 
	if (ft_strncmp(split[0], "export", ft_strlen(split[0])) != 0)
	{
		ft_free_split(split);
		return (-1);
	}
	j = 0;
	while (split[j])
		j++;
	status = EXIT_SUCCESS;
	if (j == 1)
		print_vars(); // Надо обработать сохранение экспортов без '=' append'ом и значения с $ (PATH, USER, ...)
	status = handle_export(split, j);
	ft_free_split(split);
	return (status);
}