/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrusco <bbrusco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:54:52 by bbrusco           #+#    #+#             */
/*   Updated: 2021/10/13 16:49:59 by bbrusco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*leak(char *s, int j)
{
	int	i;

	i = -1;
	while (++i < j)
		free((void *)s + i);
	free(s);
	return (NULL);
}

int	ft_sep(char b, char c)
{
	if (b == c)
		return (1);
	return (0);
}

int	ft_wcounter(char *s, char c)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && ft_sep(s[i], c))
			i++;
		if (s[i] && !(ft_sep(s[i], c)))
		{
			while (s[i] && !(ft_sep(s[i], c)))
				i++;
			j++;
		}
	}
	return (j);
}

char	*ft_edstrdup(char *s, char c)
{
	int		i;
	char	*buf;

	i = 0;
	while (s[i] && !(ft_sep(s[i], c)))
		i++;
	buf = malloc(sizeof(char) * (i + 1));
	if (!buf)
		return (leak(s, i));
	i = 0;
	while (s[i] && !(ft_sep(s[i], c)))
	{
		buf[i] = s[i];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}

char	**ft_split(char const *s, char c)
{
	char	**par;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	par = malloc(sizeof(char *) * (ft_wcounter((char *)s, c) + 1));
	if (!par)
		return (NULL);
	while (*s)
	{
		while (*s && ft_sep(*s, c))
			s++;
		if (*s && !(ft_sep(*s, c)))
		{
			par[i] = ft_edstrdup((char *)s, c);
			i++;
			while (*s && !(ft_sep(*s, c)))
				s++;
		}
	}
	par[i] = 0;
	return (par);
}
