/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:21:28 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/16 03:46:58 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_init_cmd_struct(t_cmd *cmd, char *key)
{
	cmd->id = 0;
	cmd->err_no = 0;
	cmd->status = 0;
	cmd->pid = 0;
	cmd->fd_in = 0;
	cmd->fd_out = 0;
	cmd->rd = NULL;
	cmd->name = key;
	cmd->param = (char **) NULL;
	cmd->arg = (char **) NULL;
	cmd->bin = NULL;
}

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
