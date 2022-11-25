/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:21:30 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/25 05:03:13 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_init_cmd_struct(t_cmd *cmd, char *key)
{
	cmd->id = 0;
	cmd->pid = 0;
	cmd->status = 0;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = NULL;
	cmd->delim = NULL;
	cmd->heredoc = NULL;
	cmd->name = key;
	cmd->param = (char **) NULL;
	cmd->arg = (char **) NULL;
	cmd->bin = NULL;
}

static void	assign_a_type(t_list **token)
{
	t_list	*tmp;

	tmp = *token;
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

// static void	*define_param(t_list *token)
// {
// 	t_list	*tmp;
// 	t_list	*param;

// 	token = token->next;
// 	if (!token)
// 		return (NULL);
// 	tmp = NULL;
// 	param = NULL;
// 	while (token)
// 	{
// 		if (token->type != WORD)
// 			return ((void *)param);
// 		tmp = ft_lstnew(token->val);
// 		if (!tmp)
// 			return (NULL);
// 		ft_lstadd_back(&param, tmp);
// 		token = token->next;
// 	}
// 	return ((void *)param);
// }

// static void	ft_param_n_arg(t_list *token, t_cmd *cmd)
// {
// 	t_list	*param;

// 	cmd->arg = ft_malloc_double_p(token);
// 	if (!cmd->arg)
// 		return ;
// 	param = define_param(token);
// 	if (!param)
// 		return ;
// 	cmd->param = ft_malloc_double_p(param);
// 	if (!cmd->param)
// 		return ;
// 	return ;
// }

// static void	*make_cmd(t_list *token)
// {
// 	t_cmd	*cmd;

// 	if (token->type == WORD)
// 	{
// 		cmd = ft_new_cmd(token);
// 		if (!cmd)
// 			return (NULL);
// 		ft_init_cmd_struct(cmd, token->val);
// 		ft_param_n_arg(token, cmd);
// 	}
// 	else
// 		return (NULL);
// 	return ((void *)cmd);
// }

// static void	*final_token(t_list **token)
// {
// 	t_list	*new;

// 	if ((*token)->type == VOID)
// 		*token = (*token)->next;
// 	new = ft_tokenjoin(token);
// 	if (!new)
// 		return (NULL);
// 	assign_a_type(new);
// 	return ((void *)new);
// }

/*
** Takes a ilst of token
** Then parse each token in order to return a list of cmd
** Each cmd has its args and its fd etc ...
*/
// void	*ft_cmd(t_list **token)
// {
// 	t_cmd	*cmd;
// 	t_list	*tmp;

// 	tmp = final_token(token);
// 	cmd = (t_cmd *)make_cmd(tmp);
// 	if (!cmd)
// 		return (NULL);
// 	while (tmp)
// 	{
// 		if (tmp->type == PIPE)
// 		{
// 			tmp = tmp->next;
// 			if (tmp)
// 				ft_cmd_addback(&cmd, (t_cmd *)make_cmd(tmp));
// 			else
// 				break ;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return ((void *)cmd);
// }

/*
************************************************
** NEW VERSION
** Better way to re-tokenize
************************************************
*/

void	*ft_pre_cmd(t_list **token)
{
	char	*s;
	t_list	*tmp;

	s = (char *)join_token(*token);
	if (!s)
		return (NULL);
	tmp = (t_list *)ft_tokeniser((void *)s, "|>< ");
	if (!tmp)
		return (NULL);
	return ((void *)tmp);
}

static void	*rm_void_token(t_list **token)
{
	t_list	*tmp;
	t_list	*new_token;

	tmp = *token;
	new_token = NULL;
	while (tmp)
	{
		if (tmp->type == VOID)
			tmp = tmp->next;
		new_token = ft_lstnew(tmp->val);
		ft_lstadd_back(&new_token, new_token);
		tmp = tmp->next;
	}
	return ((void *)new_token);
}

// static void	init_rd(t_cmd *cmd, t_list *token)
// {
// 	if (token->type == RD && token->next && token->next->type == WORD)
// 	{
// 		if (!ft_strcmp(token->val, "<"))
// 			cmd->infile = (char *)token->next->val;
// 		else if (!ft_strcmp(token->val, ">"))
// 			cmd->outfile = (char *)token->next->val;
// 		else if (!ft_strcmp(token->val, ">>"))
// 			cmd->append = (char *)token->next->val;
// 		else if (!ft_strcmp(token->val, "<<"))
// 			cmd->heredoc = (char *)token->next->val;
// 	}
// }

static void	*init_param(t_list *token)//, t_cmd *cmd)
{
	t_list	*param;

	token = token->next;
	if (!token)
		return (NULL);
	param = NULL;
	while (token)
	{
		if (token->type == WORD)
			ft_lstadd_back(&param, ft_lstnew(token->val));
		else if (token->type == RD)
		{
			// init_rd(cmd, token);
			token = token->next->next;
			if (token && token->type == WORD)
				ft_lstadd_back(&param, ft_lstnew(token->val));
		}
		if (token->type == PIPE)
			break ;
		token = token->next;
	}
	return ((void *)param);
}

static void	param_n_arg(t_list *token, t_cmd *cmd)
{
	t_list	*arg;
	t_list	*param;

	param = init_param(token);//, cmd);
	if (!param)
		return ;
	cmd->param = ft_malloc_double_p(param);
	if (!cmd->param)
		return ;
	arg = param;
	if (cmd->name)
		ft_lstadd_front(&arg, ft_lstnew(cmd->name));
	cmd->arg = ft_malloc_double_p(arg);
	if (!cmd->arg)
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
		param_n_arg(token, cmd);
	}
	else
		return (NULL);
	return ((void *)cmd);
}

void	*final_token(t_list **token)
{
	t_list	*tmp;

	if ((*token)->type == VOID)
		(*token) = (*token)->next;
	tmp = ft_pre_cmd(token);
	ft_type(&tmp);
	if (!tmp)
		return (NULL);
	tmp = rm_void_token(&tmp);
	if (!tmp)
		return (NULL);
	printf("BEFORE ASSIGN TYPE\n");
	assign_a_type(&tmp);
	return (tmp);
}

void	*ft_cmd(t_list **token)
{
	t_cmd	*cmd;
	t_list	*tmp;

	print_token(*token);
	tmp = final_token(token);
	cmd = (t_cmd *)make_cmd(tmp);
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
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
