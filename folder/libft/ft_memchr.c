/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrusco <bbrusco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:12:33 by bbrusco           #+#    #+#             */
/*   Updated: 2021/10/08 17:19:04 by bbrusco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*k;
	size_t		i;

	k = (const char *)s;
	i = 0;
	while (i < n)
	{
		if (*(k + i) == (char)c)
			return ((void *)k + i);
		i++;
	}
	return (NULL);
}
