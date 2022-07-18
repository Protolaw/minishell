
#include "../inc/env.h"

int	ft_init_env()
{
	extern char	**environ;
	int			i;

	i = split_count(environ);
	if (i == 0)
		return (0);
	g_env = malloc((i + 1) * sizeof(char *));
	if (g_env == NULL)
		return (1);
	i = -1;
	while (environ[++i])
	{
		g_env[i] = ft_strdup(environ[i]);
		if (g_env[i] == NULL)
		{
			ft_free_split(g_env);
			return (1);
		}
	}
	g_env[i] = NULL;
	return (0);
}

char	*env_find_var(char *key)
{
	int	len;
	int	i;

	if (key == NULL || g_env == NULL)
		return (NULL);
	if (ft_strchr(key, '='))
		len = ft_strchr(key, '=') - key;
	else
		len = ft_strlen(key);
	i = -1;
	while (g_env[++i])
		if (!ft_strncmp(key, g_env[i], len) && g_env[i][len] == '=')
			return (g_env[i]);
	return (NULL);
}

char	*get_value_env(char *key)
{
	char	*env_var;

	env_var = env_find_var(key);
	if (env_var)
		return (ft_strchr(env_var, '=') + 1);
	else
		return (NULL);
}

int	env_var_is_value(char *var_name, char *value)
{
	char	*env_value;

	env_value = get_value_env(var_name);
	if (env_value)
		if (ft_strncmp(env_value, value, ft_strlen(value) + 1) == 0)
			return (1);
	return (0);
}