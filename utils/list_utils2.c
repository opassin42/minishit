/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:44:41 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/17 20:12:32 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst && del)
	{
		del(lst->val);
		free((void *)lst);
	}
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*elem;

	if (*lst && del)
	{
		while (*lst)
		{
			elem = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = elem;
		}
		*lst = NULL;
	}
}

void	ft_lst_prevlast(t_list **list)
{
	t_list	*last;
	t_list	*prev_last;

	last = *list;
	prev_last = *list;
	while (last->next)
	{
		prev_last = last;
		last = last->next;
	}
	prev_last->next = NULL;
}

void	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*new;
	void	*elem;
	void	*c;

	new = NULL;
	while (lst)
	{
		c = f(lst->val);
		elem = ft_lstnew(c);
		if (!elem)
		{
			ft_lstclear(&lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new, elem);
		lst = lst->next;
	}
	return ((void *)new);
}
