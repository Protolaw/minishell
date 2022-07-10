/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrusco <bbrusco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 12:36:39 by bbrusco           #+#    #+#             */
/*   Updated: 2022/07/10 17:46:45 by bbrusco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	i = 0;
	while (environ[i])
	{
		g_env[i] = ft_strdup(environ[i]);
		if (g_env[i] == NULL)
		{
			ft_free_split(g_env);
			return (1);
		}
		i++;
	}
	g_env[i] = NULL;
	return (0);
}

// Печать переменных окружения

int	ft_print_env(char **env)
{
	int	i;

	if (env == NULL)
		return (ft_err_print("Error: env not set\n"));
	i = 0;
	while (env[i])
		ft_putendl_fd(env[i++], 1);
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
	i = 0;
	while (g_env[i])
	{
		if (!ft_strncmp(key, g_env[i], len) && g_env[i][len] == '=')
			return (g_env[i]);
		i++;
	}
	return (NULL);
}