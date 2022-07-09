/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrusco <bbrusco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 09:52:23 by bbrusco           #+#    #+#             */
/*   Updated: 2021/10/10 16:33:57 by bbrusco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	in_range(const char	*str)
{
	if ((*str == ' ') || (*str == '\f') || (*str == '\n') || (*str == '\r')
		|| (*str == '\t') || (*str == '\v'))
		return (1);
	return (0);
}

int	ft_atoi(const char	*str)
{
	LLI	nbr;
	LLI	i;

	i = 0;
	nbr = 0;
	while (in_range(str) == 1)
		str++;
	if ((*str == '-') || (*str == '+'))
	{	
		if (*str == '-')
			i++;
		str++;
	}
	while ((*str >= '0') && (*str <= '9'))
	{
		nbr = (nbr * 10) + (LLI)(*(str) - '0');
		str++;
	}
	if (i % 2 == 0)
		return (nbr);
	else
		return (nbr * (-1));
}
