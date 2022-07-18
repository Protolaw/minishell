
#include "../inc/env.h"

int	env_unset_var(char *name)
{
	char	*env_var;

	env_var = env_find_var(name);
	if (env_var == NULL)
		return (-1);
	env_rm_value(&g_env, env_var);
	return (0);
}

int	env_put_var(char *str)
{
	char	*old_var;
	char	*new_var;
	int		status;

	if (str == NULL || ft_strchr(str, '=') == NULL)
		return (-1);
	new_var = ft_strdup(str);
	if (new_var == NULL)
		return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
	old_var = env_find_var(str);
	status = env_replace_value(&g_env, old_var, new_var);
	if (status == -1)
	{
		status = env_add_value(&g_env, new_var);
		if (status == -1)
			return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
	}
	return (0);
}

int	env_set_env(char *name, char *value)
{
	char	*var_str;
	char	*tmp;
	int		status;

	if (name == NULL || value == NULL)
		return (-1);
	tmp = ft_strjoin(name, "=");
	if (tmp == NULL)
		return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
	var_str = ft_strjoin(tmp, value);
	free(tmp);
	if (var_str == NULL)
		return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
	status = env_put_var(var_str);
	free(var_str);
	return (status);
}
