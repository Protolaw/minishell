/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrusco <bbrusco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 12:36:39 by bbrusco           #+#    #+#             */
/*   Updated: 2022/07/09 15:43:15 by bbrusco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	ft_init_env(char **env)
{
	extern char	**environ;
	int			i;

	i = split_count(environ);
	if (i == 0)
		return (0);
	env = malloc((i + 1) * sizeof(char *));
	if (env == NULL)
		return (ft_err_print("msg"));
	i = 0;
	while (environ[i])
	{
		env[i] = ft_strdup(environ[i]);
		if (env[i] == NULL)
		{
			ft_free_split(env);
			return (ft_err_print("msg"));
		}
		i++;
	}
	env[i] = NULL;
	return (0);
}