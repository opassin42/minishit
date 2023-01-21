/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:55:21 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/21 04:23:27 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	init_cmd(t_cmd *cmd, char *key)
{
	cmd->i = -1;
	cmd->id = -1;
	cmd->pid = 0;
	cmd->ret = 0;
	cmd->fd[0] = 0;
	cmd->fd[1] = 0;
	cmd->append = 0;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->name = key;
	cmd->param = (char **) NULL;
	cmd->arg = (char **) NULL;
	cmd->bin = NULL;
	cmd->rd = (t_rd *) NULL;
}

static void	*init_arg(t_list *token, t_cmd *cmd)
{
	t_list	*arg;

	arg = NULL;
	while (token)
	{
		if (token->type == WORD)
			ft_lstadd_back(&arg, ft_lstnew(token->val));
		if (token->type == RD)
		{
			init_rd(cmd, token);
			token = token->next;
			if (!token)
				break ;
		}
		if (token && token->type == PIPE)
			break ;
		token = token->next;
	}
	return ((void *)arg);
}

static void	init_cmd_arg(t_list *token, t_cmd *cmd)
{
	t_list	*arg;
	t_list	*param;

	arg = (t_list *)init_arg(token, cmd);
	if (!arg)
		return ;
	cmd->arg = ft_malloc_double_p(arg);
	if (!cmd->arg)
		return ;
	param = arg->next;
	cmd->param = ft_malloc_double_p(param);
	if (!cmd->param)
		return ;
	return ;
}

/*
** Get the address of the token
** How to create the first cmd beginning with RD
** Returns (void *)cmd
*/
void	*first_cmd(t_list **token)
{
	t_list	*rd;
	t_list	*tmp;
	t_cmd	*cmd;

	tmp = *token;
	if (tmp && tmp->type == RD)
	{
		rd = tmp;
		tmp = tmp->next;
		if (tmp && tmp->type == WORD)
		{
			tmp = tmp->next;
			if (tmp)
			{
				cmd = ft_new_cmd(tmp);
				if (!cmd)
					return (NULL);
				init_cmd(cmd, tmp->val);
				return (init_rd(cmd, rd), init_cmd_arg(tmp, cmd), (void *)cmd);
			}
			if (input_without_cmd(token))
				return (NULL);
		}
	}
	return (NULL);
}

void	*make_cmd(t_list *token)
{
	t_cmd	*cmd;

	if (token->type == WORD)
	{
		cmd = ft_new_cmd(token);
		if (!cmd)
			return (NULL);
		init_cmd(cmd, token->val);
		init_cmd_arg(token, cmd);
	}
	else
		return (NULL);
	return ((void *)cmd);
}
