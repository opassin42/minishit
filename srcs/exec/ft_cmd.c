/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:21:30 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/20 16:48:39 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	assign_a_type(t_list *token)
{
	t_list	*tmp;

	tmp = token;
	while (tmp)
	{
		tmp->type = -1;
		if (!word_type(tmp->val))
			tmp->type = WORD;
		else if (!pipe_type(tmp->val))
			tmp->type = PIPE;
		else if (!rd_type(tmp->val))
			tmp->type = RD;
		tmp = tmp->next;
	}
}

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
	tmp = NULL;
	param = NULL;
	while (token)
	{
		if (token->type != WORD)
			return ((void *)param);
			// break ;
		tmp = ft_lstnew(token->val);
		if (!tmp)
			return (NULL);
		ft_lstadd_back(&param, tmp);
		token = token->next;
	}
	return ((void *)param);
}

static void	ft_param_n_arg(t_list *token, t_cmd *cmd)
{
	t_list	*param;

	cmd->arg = ft_malloc_double_p(token);
	if (!cmd->arg)
		return ;
	param = define_param(token);
	if (!param)
		return ;
	cmd->param = ft_malloc_double_p(param);
	if (!cmd->param)
		return ;
	return ;
}

static void	*make_cmd(t_list *token)
{
	t_cmd	*cmd;

	if (token->type == WORD)
	{
		cmd = ft_new_cmd(token);
		if (!cmd)
			return (NULL);
		ft_init_cmd_struct(cmd, token->val);
		ft_param_n_arg(token, cmd);
	}
	else
		return (NULL);
	return ((void *)cmd);
}

static void	*final_token(t_list **token)
{
	t_list	*new;

	if ((*token)->type == VOID)
		*token = (*token)->next;
	new = ft_tokenjoin(token);
	if (!new)
		return (NULL);
	assign_a_type(new);
	print_token(new);
	return ((void *)new);
}

/*
** Takes a ilst of token
** Then parse each token in order to return a list of cmd
** Each cmd has its args and its fd etc ...
*/
void	*ft_cmd(t_list **token)
{
	t_cmd	*cmd;
	t_list	*tmp;

	tmp = final_token(token);
	cmd = (t_cmd *)make_cmd(tmp);
	if (!cmd)
		return (NULL);
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			tmp = tmp->next;
			// if (tmp && tmp->type == VOID)
			// 	tmp = tmp->next;
			if (tmp)
				ft_cmd_addback(&cmd, (t_cmd *)make_cmd(tmp));
			else
				break ;
		}
		tmp = tmp->next;
	}
	return ((void *)cmd);
}
