/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrusco <bbrusco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:01:30 by bbrusco           #+#    #+#             */
/*   Updated: 2021/10/08 17:19:28 by bbrusco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*sr;
	char	*ds;
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	sr = (char *)src;
	ds = (char *)dst;
	if (sr < ds)
		while ((int)(--len) >= 0)
			*(ds + len) = *(sr + len);
	else
	{
		while (i < len)
		{
			*(ds + i) = *(sr + i);
			i++;
		}
	}
	return (dst);
}
