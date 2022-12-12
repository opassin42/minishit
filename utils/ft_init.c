/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 03:35:24 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/12 03:54:18 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data	init_global(void)
{
	t_data	g_data;

	g_data.status = 0;
	g_data.sigint = 0;
	g_data.sigquit = 0;
	g_data.pid = -1;
	g_data.gc = 0;
	g_data.keeprunning = 1;
	return (g_data);
}

// void	ft_free_token(t_list **token, void (*clr)(void*))
// {
// 	t_list	*elem;
// 	t_list	*next;

// 	elem = *token;
// 	if (*token && clr)
// 	{
// 		while (elem)
// 		{
// 			next = elem->next;
// 			clr(elem);
// 			elem = next;
// 		}
// 		*token = NULL;
// 	}
// }

// void	*ft_realloc(char *s, size_t new_len)
// {
// 	size_t	len;
// 	char	*p;

// 	len = (size_t)ft_strlen(s);
// 	if (len < new_len || len > new_len)
// 	{
// 		p = (char *)push_top(&g_data.gc, sizeof(char) * ((int)new_len + 1));
// 		if (!p)
// 			return (gc_free(), NULL);
// 		p = (char *)ft_memcpy(p, s, ft_strlen(s));
// 		return ((void *)p);
// 	}
// 	return ((void *)s);
// }
