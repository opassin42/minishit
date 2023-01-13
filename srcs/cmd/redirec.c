/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 05:04:34 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/13 16:50:47 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	input_without_cmd(t_list **token)
{
	int		fd;
	t_list	*tmp;

	fd = 0;
	tmp = *token;
	if (tmp && tmp->type == RD)
	{
		if (tmp->next && !tmp->next->next)
		{
			if (!ft_strcmp(tmp->val, ">"))
				fd = open(tmp->next->val, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			else if (!ft_strcmp(tmp->val, ">>"))
				fd = open(tmp->next->val, O_WRONLY | O_CREAT | O_APPEND, 0666);
			else if (!ft_strcmp(tmp->val, "<"))
				if (open(tmp->next->val, O_RDONLY, 0666) == -1)
					cmd_error((char *)tmp->next->val, ERRNO_3, 2, ft_putstr_fd);
			if (fd == -1)
				return ;
		}
	}
}

static int	rd_in(t_cmd *cmd)
{
	if (cmd->hdoc)
		printf("heredoc detected\n");
	else
		cmd->ret = open(cmd->infile, O_RDONLY, 0666);
	cmd->fd_in = dup(STDIN_FILENO);
	if (cmd->ret == -1)
		return (errno);
	dup2(cmd->ret, STDIN_FILENO);
	return (EXIT_SUCCESS);
}

static int	rd_out(t_cmd *cmd)
{
	if (!cmd->append)
		cmd->ret = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		cmd->ret = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
	cmd->fd_out = dup(STDOUT_FILENO);
	if (cmd->ret == -1)
		return (errno);
	dup2(cmd->ret, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

void	init_rd(t_cmd *cmd, t_list *token)
{
	if (!ft_strcmp((char *)token->val, "<")
		|| !ft_strcmp((char *)token->val, "<<"))
	{
		cmd->infile = (char *)token->next->val;
		if (!ft_strcmp((char *)token->val, "<<"))
			cmd->hdoc = 1;
		else
			cmd->hdoc = 0;
		if (rd_in(cmd) != EXIT_SUCCESS)
			cmd_error((char *)token->next->val, ERRNO_3, 2, ft_putstr_fd);
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
