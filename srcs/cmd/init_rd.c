/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:03:11 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/20 18:21:58 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	define_rd(char *s)
{
	if (!ft_strcmp(s, ">"))
		return (1);
	if (!ft_strcmp(s, ">>"))
		return (2);
	if (!ft_strcmp(s, "<"))
		return (3);
	return (0);
}

static t_rd	*new_rd(t_list *token)
{
	t_rd	*rd;

	rd = (t_rd *)push_top(&g_data.gc, sizeof(t_rd));
	if (!rd)
		return (gc_free(), NULL);
	rd->flag = define_rd((char *)token->val);
	token = token->next;
	if (token)
		rd->file = (char *)token->val;
	else
		rd->file = NULL;
	rd->next = NULL;
	return (rd);
}

static t_rd	*last_rd(t_rd *rd)
{
	if (rd)
	{
		while (rd->next)
			rd = rd->next;
	}
	return (rd);
}

static void	rd_addback(t_rd **rd, t_rd *new_rd)
{
	if (new_rd)
	{
		if (*rd)
			last_rd(*rd)->next = new_rd;
		else
			*rd = new_rd;
	}
}

void	init_rd(t_cmd *cmd, t_list *token)
{
	t_rd	*rd;

	rd = new_rd(token);
	if (!rd)
		return ;
	rd_addback(&cmd->rd, rd);
}
