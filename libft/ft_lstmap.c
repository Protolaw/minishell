/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrusco <bbrusco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:28:46 by bbrusco           #+#    #+#             */
/*   Updated: 2021/10/13 16:47:00 by bbrusco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*content;
	t_list	*ed_lst;
	t_list	*last;
	t_list	*cell;

	last = NULL;
	ed_lst = NULL;
	while (lst)
	{
		content = f(lst->content);
		cell = ft_lstnew(content);
		if (!cell)
		{
			if (!ed_lst)
				ft_lstclear(&ed_lst, del);
			return (NULL);
		}
		if (!ed_lst)
			ed_lst = cell;
		if (last)
			last->next = cell;
		last = cell;
		lst = lst->next;
	}
	return (ed_lst);
}
