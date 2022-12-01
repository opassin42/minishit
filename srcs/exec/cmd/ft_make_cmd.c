/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 02:32:23 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/01 08:12:58 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	init_rd(t_cmd *cmd, t_list *token)
{
	if (token->type == RD)
	{
		if (!ft_strcmp((char *)token->val, "<"))
			cmd->infile = (char *)token->next->val;
		else if (!ft_strcmp((char *)token->val, ">"))
			cmd->outfile = (char *)token->next->val;
		else if (!ft_strcmp((char *)token->val, ">>"))
			cmd->append = (char *)token->next->val;
		// else if (!ft_strcmp((char *)token->val, "<<"))
		// 	*cmd->heredoc = (char *)token->next->val;
	}
}

static void	ft_init_cmd_struct(t_cmd *cmd, char *key)
{
	cmd->id = 0;
	cmd->pid = 0;
	cmd->status = 0;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = NULL;
	cmd->delim = NULL;
	cmd->name = key;
	cmd->param = (char **) NULL;
	cmd->arg = (char **) NULL;
	cmd->bin = NULL;
	cmd->heredoc = (char **) NULL;
}

static void	*init_arg(t_list *token, t_cmd *cmd)
{
	t_list	*arg;

	arg = NULL;
	while (token)
	{
		if (token->type == WORD)
			ft_lstadd_back(&arg, ft_lstnew(token->val));
		else if (token->type == RD)
		{
			init_rd(cmd, token);
			token = token->next;
			if (!token)
				break ;
		}
		// printf("cmd->file : \n\tin - [%s]\n\tout - [%s]\n\tappend : [%s]\n", cmd->infile, cmd->outfile, cmd->append);
		if (token->type == PIPE)
			break ;
		token = token->next;
	}
	return ((void *)arg);
}

static void	param_n_arg(t_list *token, t_cmd *cmd)
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
	// if (cmd->outfile)
	// 	open(cmd->outfile, O_CREAT);
	return ;
}

void	*make_cmd(t_list *token)
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
