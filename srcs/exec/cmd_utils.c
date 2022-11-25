/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:21:28 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/25 03:41:24 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*ft_new_cmd(t_list *token)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)push_top(&start, sizeof(t_cmd));
	if (!cmd)
		return (gc_free(), NULL);
	cmd->name = (char *)token->val;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*ft_last_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		while (cmd->next)
			cmd = cmd->next;
	}
	return (cmd);
}

void	ft_cmd_addback(t_cmd **cmd, t_cmd *new_cmd)
{
	if (new_cmd)
	{
		if (*cmd)
			ft_last_cmd(*cmd)->next = new_cmd;
		else
			*cmd = new_cmd;
	}
}

void	*join_token(t_list *token)
{
	char	*s;
	t_list	*tmp;

	tmp = token;
	s = tmp->expand;
	tmp = tmp->next;
	while (tmp)
	{
		s = ft_strjoin(s, tmp->expand);
		if (!s)
			return (NULL);
		tmp = tmp->next;
	}
	return ((void *)s);
}
