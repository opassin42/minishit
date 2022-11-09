/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage_collector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opassin <ccouliba@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:42:36 by opassin           #+#    #+#             */
/*   Updated: 2022/10/05 04:42:38 by opassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_gblst	*init_gbc(void *elem)
{
	t_gblst el;

	el = malloc (sizeof(t_gblst));
	if (!elem)
		return (NULL);
	el->addr = elem;
	el->next = NULL;
	return (el);
}

int	add_gb(void *gblst, void *elem)
{
	t_gblst *tmp;

	tmp = (t_gblst)gblst;
	while (tmp)
		tmp = tmp->next;
	tmp = init_gbc(void *elem);
	if (tmp)
		return (0);
	return (1);
}

int	ft_gbc(void *gblst)
{
	void	*tmp;

	tmp = gblst;
	while (tmp)
	{
		gblst = gblst->next;
		free(tmp);
		tmp = gblst;
	}
	return (1)
}