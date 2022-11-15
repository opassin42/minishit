/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:21:30 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/15 17:33:10 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	assign_a_type(t_list **token)
{
	t_list	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (!word_type(tmp->val))
			tmp->type = WORD;
		else if (!pipe_type(tmp->val))
			tmp->type = PIPE;
		else if (!rd_type(tmp->val))
			tmp->type = RD;
		tmp = tmp->next;
	}
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
		if (token->type == WORD)
		{
			tmp = ft_lstnew(token->val);
			if (!tmp)
				return (NULL);
			ft_lstadd_back(&param, tmp);
		}
		else
			break ;
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

void	*ft_cmd(t_list **token)
{
	t_list	*tmp;
	t_cmd	*cmd;

	tmp = ft_tokenjoin(token);
	if (!tmp)
		return (NULL);
	assign_a_type(&tmp);
	cmd = (t_cmd *)make_cmd(tmp);
	if (!cmd)
		return (NULL);
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			tmp = tmp->next;
			if (tmp && tmp->type == VOID)
				tmp = tmp->next;
			if (tmp)
				ft_cmd_addback(&cmd, (t_cmd *)make_cmd(tmp));
			else
				break ;
		}
		tmp = tmp->next;
	}
	return ((void *)cmd);
}
