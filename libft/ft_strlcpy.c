/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrusco <bbrusco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 09:52:23 by bbrusco           #+#    #+#             */
/*   Updated: 2021/10/08 15:26:41 by bbrusco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char	*dest, const char	*src, size_t	dstsize)
{
	size_t	i;
	size_t	c;

	c = 0;
	while (src[c])
		c++;
	if (dstsize == 0)
		return (c);
	i = 0;
	while (src[i] && (i < dstsize - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (c);
}
