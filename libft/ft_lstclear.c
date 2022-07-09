/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrusco <bbrusco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:28:46 by bbrusco           #+#    #+#             */
/*   Updated: 2021/10/13 16:46:36 by bbrusco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*buf;
	t_list	*start;

	start = *lst;
	while (start)
	{
		buf = start->next;
		if (del)
			del(start->content);
		free(start);
		start = buf;
	}
	*lst = NULL;
}
