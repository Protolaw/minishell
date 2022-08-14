/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrusco <bbrusco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:39:38 by bbrusco           #+#    #+#             */
/*   Updated: 2021/10/09 17:24:52 by bbrusco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	bytestotal;
	void	*address;

	bytestotal = count * size;
	address = malloc(bytestotal);
	if (!address)
		return (NULL);
	if (address)
		ft_memset(address, 0, bytestotal);
	return (address);
}
