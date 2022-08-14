/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrusco <bbrusco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:05:21 by bbrusco           #+#    #+#             */
/*   Updated: 2021/10/13 17:00:42 by bbrusco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*p;
	char	*p2;

	p = (char *)dst;
	p2 = (char *)src;
	i = 0;
	while (i < n && p != p2)
	{
		*(p + i) = *(p2 + i);
		i++;
	}
	return (dst);
}
