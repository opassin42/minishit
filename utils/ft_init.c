/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 03:35:24 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/15 17:46:15 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_token(t_list **token, void (*clr)(void*))
{
	t_list	*elem;
	t_list	*next;

	elem = *token;
	if (*token && clr)
	{
		while (elem)
		{
			next = elem->next;
			clr(elem);
			elem = next;
		}
		*token = NULL;
	}
}

void	*ft_realloc(char *s, size_t new_len)
{
	size_t	len;
	char	*p;

	len = (size_t)ft_strlen(s);
	if (len < new_len || len > new_len)
	{
		p = (char *)push_top(&start, sizeof(char) * ((int)new_len + 1));
		p = (char *)ft_memcpy(p, s, ft_strlen(s));
		if (!p)
		{
			gc_free();
			return (NULL);
		}
		return ((void *)p);
	}
	return ((void *)s);
}
