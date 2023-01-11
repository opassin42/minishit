/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 02:32:23 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/10 21:16:46 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	init_cmd_struct(t_cmd *cmd, char *key)
{
	cmd->id = 0;
	cmd->pid = 0;
	cmd->status = 0;
	cmd->ret = 0;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->append = 0;
	cmd->infile = NULL;
	cmd->outfile = NULL;
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
		if (token && token->type == PIPE)
			break ;
		token = token->next;
	}
	return ((void *)arg);
}

static void	init_param_arg(t_list *token, t_cmd *cmd)
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

void	*start_with_rd(t_list **token, t_cmd *cmd)
{
	int		rd;
	char	*file;
	t_list	*tmp;

	rd = -1;
	tmp = *token;
	if (tmp && tmp->type == RD)
	{
		rd = witch_rd(tmp->val);
		tmp = tmp->next;
		if (!tmp)
			return (NULL);
		file = tmp->val;
		tmp = tmp->next;
		if (tmp && tmp->type == WORD)
		{
			cmd = ft_new_cmd(tmp);
			if (!cmd)
				return (NULL);
		}
		else
			return (NULL);
	}
	return ((void *)cmd);
}

void	*make_cmd(t_list *token)
{
	t_cmd	*cmd;

	if (token->type == WORD)
	{
		cmd = ft_new_cmd(token);
		if (!cmd)
			return (NULL);
		init_cmd_struct(cmd, token->val);
		init_param_arg(token, cmd);
	}
	else
		return (NULL);
	return ((void *)cmd);
}
