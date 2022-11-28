/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:21:30 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/26 02:30:54 by ccouliba         ###   ########.fr       */
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

/*
************************************************
** NEW VERSION
** Better way to re-tokenize
************************************************
*/
void	*ft_pre_cmd(t_list *token)
{
	char	*s;
	t_list	*tmp;

	s = (char *)join_token(token);
	if (!s)
		return (NULL);
	tmp = (t_list *)ft_tokeniser((void *)s, "|>< ");
	if (!tmp)
		return (NULL);
	ft_type(&tmp);
	return ((void *)tmp);
}

/*
** valgrind : "AddressSanitizer: SEGV srcs/exec/ft_cmd.c:85 in rm_void_token"
*/
static void	*rm_void_token(t_list *token)
{
	t_list	*tmp;
	t_list	*new;

	tmp = token;
	new = NULL;
	if (tmp->type == VOID)
		tmp = tmp->next;
	new = ft_lstnew(tmp->val);
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type == VOID)
			tmp = tmp->next;
		ft_lstadd_back(&new, ft_lstnew(tmp->val));
		tmp = tmp->next;
	}
	return ((void *)new);
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

static void	*init_arg(t_list *token)
{
	t_list	*arg;

	arg = NULL;
	while (token)
	{
		if (token->type == WORD)
			ft_lstadd_back(&arg, ft_lstnew(token->val));
		else if (token->type == RD)
		{
			// init_rd(cmd, token);
			token = token->next->next;
			if (token && token->type == WORD)
				ft_lstadd_back(&arg, ft_lstnew(token->val));
		}
		else if (token->type == PIPE)
			break ;
		token = token->next;
	}
	return ((void *)arg);
}

static void	param_n_arg(t_list *token, t_cmd *cmd)
{
	t_list	*arg;
	t_list	*param;

	arg = init_arg(token);
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
	t_list	*new;
	t_list	*pre_cmd;
	t_list	*tmp;

	tmp = *token;
	if (tmp->type == VOID)
		tmp = tmp->next;
	pre_cmd = (t_list *)ft_pre_cmd(tmp);
	if (!pre_cmd)
		return (NULL);
	new = (t_list *)rm_void_token(pre_cmd);
	if (!new)
		return (NULL);
	assign_a_type(&new);
	return (new);
}

void	positive_hashing(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((int)s[i] < 0)
			s[i] = (int)s[i] * -1;
		++i;
	}
}

void	hash_token(t_list *token)
{
	while (token)
	{
		positive_hashing(token->val);
		token = token->next;
	}
}

void	*ft_cmd(t_list **token)
{
	t_cmd	*cmd;
	t_list	*tmp;

	tmp = final_token(token);
	hash_token(tmp);
	cmd = (t_cmd *)make_cmd(tmp);
	if (!cmd)
		return (NULL);
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			tmp = tmp->next;
			if (tmp)
				ft_cmd_addback(&cmd, (t_cmd *)make_cmd(tmp));
			else
				return ((void *)cmd);
		}
		tmp = tmp->next;
	}
	return ((void *)cmd);
}
