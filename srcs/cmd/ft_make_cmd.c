/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 02:32:23 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/10 23:57:05 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_init_cmd_struct(t_cmd *cmd, char *key)
{
	cmd->id = 0;
	cmd->pid = 0;
	cmd->status = 0;
	cmd->ret = STDOUT_FILENO;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->append = 0;
	cmd->finalfdin = 0;
	cmd->finalfdout = 1;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->delim = NULL;
	cmd->name = key;
	cmd->param = (char **) NULL;
	cmd->arg = (char **) NULL;
	cmd->bin = NULL;
	cmd->heredoc = (char **) NULL;
}

int	rd_in(t_cmd *cmd)
{
	if (cmd->hdoc)
		printf("heredoc detected\n");
	else
		cmd->ret = open(cmd->infile, O_RDONLY, 0666);
	cmd->finalfdin = dup(STDIN_FILENO);
	if (cmd->ret == -1)
		return (errno);
	dup2(cmd->ret, cmd->fd_in);
	return (EXIT_SUCCESS);
}

int	rd_out(t_cmd *cmd)
{
	if (!cmd->append)
		cmd->ret = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		cmd->ret = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
	cmd->finalfdout = dup(STDOUT_FILENO);
	if (cmd->ret == -1)
		return (errno);
	dup2(cmd->ret, cmd->fd_out);
	return (EXIT_SUCCESS);
}

static void	init_rd(t_cmd *cmd, t_list *token)
{
	if (!ft_strcmp((char *)token->val, "<")
		|| !ft_strcmp((char *)token->val, "<<")){
		cmd->infile = (char *)token->next->val;
		if (!ft_strcmp((char *)token->val, "<<"))
			cmd->hdoc = 1;
		else
			cmd->hdoc = 0;
		if (rd_in(cmd) != EXIT_SUCCESS)
			printf("erreur redir in\n");
	}
	else if (!ft_strcmp((char *)token->val, ">")
		|| !ft_strcmp((char *)token->val, ">>"))
	{
		cmd->outfile = (char *)token->next->val;
		if (!ft_strcmp((char *)token->val, ">>"))
			cmd->append = 1;
		else
			cmd->append = 0;
		if (rd_out(cmd) != EXIT_SUCCESS)
			printf("erreur redir out\n");
	}
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
	return ;
}

void	*make_cmd(t_list *token)
{
	t_cmd	*cmd;

	if (token->type == WORD)
	{
		cmd = ft_new_cmd(token);
		if (!cmd)
			return (gc_free(), NULL);
		ft_init_cmd_struct(cmd, token->val);
		param_n_arg(token, cmd);
	}
	else
		return (NULL);
	return ((void *)cmd);
}
