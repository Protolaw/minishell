/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrusco <bbrusco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 09:52:23 by bbrusco           #+#    #+#             */
/*   Updated: 2021/10/13 17:10:41 by bbrusco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char	*dest, const char	*src, size_t	size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (src[j])
		j++;
	if (size == 0)
		return (j);
	while (dest[k])
		k++;
	if (size <= k)
		return (size + j);
	while (size && (--size - k) && src[i])
	{
		dest[k + i] = src[i];
		i++;
	}
	dest[i + k] = '\0';
	return (j + k);
}
