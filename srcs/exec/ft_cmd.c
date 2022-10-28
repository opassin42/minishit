/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:21:30 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/27 22:24:14 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_init_cmd_struct(t_cmd *cmd, char *key)
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

static void	*define_param(t_list *token)
{
	t_list	*tmp;
	t_list	*param;

	token = token->next;
	if (!token)
		return (NULL);
	if (token->type == WORD)
		param = ft_lstnew(token->val);
	else if (token->type == VOID)
		param = NULL;
	else
		return (NULL);
	tmp = token->next;
	while (tmp)
	{
		if (tmp->type == VOID)
			tmp = tmp->next;
		if (tmp->type == WORD)
			ft_lstadd_back(&param, ft_lstnew(tmp->expand));
		else
			break ;
		tmp = tmp->next;
	}
	return (param);
}

void	ft_param_n_arg(t_list *token, t_cmd *cmd)
{
	t_list	*arg;
	t_list	*param;

	param = (t_list *)define_param(token);
	if (!param)
		return ;
	arg = param;
	if (cmd->name)
		ft_lstadd_front(&arg, ft_lstnew((void *)(cmd->name)));
	cmd->param = ft_malloc_double_p(param);
	if (!cmd->param)
		cmd->param = (char **) NULL;
	cmd->arg = ft_malloc_double_p(arg);
	if (!cmd->arg)
		return ;
	return ;
}

static void	*create_cmd(t_list *token)
{
	t_cmd	*cmd;

	if (token->type == WORD)
	{
		cmd = ft_new_cmd(token);
		if (!cmd)
			return (NULL);
		ft_init_cmd_struct(cmd, token->expand);
		ft_param_n_arg(token, cmd);
	}
	else
		return (NULL);
	return (cmd);
}

void	*ft_cmd(t_list **token)
{
	t_list	*tmp;
	t_cmd	*cmd;

	tmp = *token;
	cmd = (t_cmd *)create_cmd(tmp);
	if (!cmd)
		return (NULL);
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			tmp = tmp->next;
			if (tmp->type == VOID)
				tmp = tmp->next;
			ft_cmd_addback(&cmd, (t_cmd *)create_cmd(tmp));
		}
		tmp = tmp->next;
	}
	return ((void *)cmd);
}
