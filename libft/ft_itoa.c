/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrusco <bbrusco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:28:46 by bbrusco           #+#    #+#             */
/*   Updated: 2021/10/10 17:17:16 by bbrusco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_find(int n, int len)
{
	while (n / 10)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	char	sign;

	sign = 1;
	if (n < 0)
		sign = -1;
	len = len_find(n, 2 + (n < 0));
	str = (char *)malloc(sizeof(char) * (len--));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	str[len--] = sign * (n % 10) + '0';
	while (n / 10)
	{
		n = n / 10;
		str[len--] = sign * (n % 10) + '0';
	}
	if (sign < 0)
		str[len] = '-';
	return (str);
}
