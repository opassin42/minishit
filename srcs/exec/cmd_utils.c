/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:21:28 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/24 03:13:55 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*ft_new_cmd(t_list *token)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
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

void	ft_init_cmd_struct(t_cmd *cmd, void *name)
{
	cmd->id = 0;
	cmd->err_no = 0;
	cmd->status = 0;
	cmd->pid = 0;
	cmd->fd_in = 0;
	cmd->fd_out = 0;
	cmd->rd = NULL;
	cmd->name = (char *)name;
	cmd->arg = (char **)NULL;
}

// char	**malloc_arg(t_list *token)
// {
// 	int		arg_nb;
// 	char	**param;

// 	arg_nb = count_arg_nb(token);
// 	if (!arg_nb)
// 		return (NULL);
// 	printf ("arg_nb = %d\n", arg_nb);
// 	param = malloc(sizeof(char *) * (arg_nb + 1));
// 	if (!param)
// 		return (NULL);
// 	token = token->next;
// 	if (token->type == VOID)
// 		token = token->next;
// 	param = (char **)fill_arg(token, param, arg_nb);
// 	if (!param)
// 		return (NULL);
// 	return (param);
// }
