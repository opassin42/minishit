/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 05:04:34 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/21 05:10:34 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	input_without_cmd(t_list **token)
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
				fd = open(tmp->next->val, O_RDONLY, 0666);
			if (fd == -1)
			{
				perror((char *)tmp->next->val);
				return (WEXITSTATUS(g_data.status));
			}
		}
	}
	return (EXIT_SUCCESS);
}

static void	open_cmd_fd(t_cmd *cmd, t_rd *rd)
{
	if (rd->flag == 1)
		cmd->fd[1] = open(rd->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (rd->flag == 2)
		cmd->fd[1] = open(rd->file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (rd->flag == 3)
		cmd->fd[0] = open(rd->file, O_RDONLY, 0666);
	if (cmd->fd[1] == -1 || cmd->fd[0] == -1)
	{
		g_data.status = 1;
		if (g_data.pfd[1] != -1)
			close(g_data.pfd[1]);
		if (g_data.pfd[0] != -1)
			close(g_data.pfd[0]);
		if (errno == 13)
			exec_error(rd->file, ERRNO_4, 2, ft_putstr_fd);
		else
			exec_error(rd->file, ERRNO_3, 2, ft_putstr_fd);
	}
}

static void	duplicate_fd(t_cmd *cmd, t_rd *rd)
{
	if (rd->flag == 3)
	{
		dup2(cmd->fd[0], STDIN_FILENO);
		close(cmd->fd[0]);
	}
	else
	{
		dup2(cmd->fd[1], STDOUT_FILENO);
		close(cmd->fd[1]);
	}
}

void	open_files(t_cmd *cmd)
{
	t_rd	*rd;

	rd = cmd->rd;
	while (rd)
	{
		open_cmd_fd(cmd, rd);
		duplicate_fd(cmd, rd);
		rd = rd->next;
	}
}

/*
// printf("open_files : cmd->name = %s | outfile = %s | cmd->fd[1] = %d | cmd->ret = %d\n", cmd->name, cmd->outfile, cmd->fd[1], cmd->ret);
// printf("open_files : cmd->name = %s | outfile = %s | cmd->fd[1] = %d | cmd->ret = %d\n", cmd->name, cmd->outfile, cmd->fd[1], cmd->ret);
// printf("open_files : cmd->name = %s | infile = %s | cmd->fd[0] = %d | cmd->ret = %d\n", cmd->name, cmd->infile, cmd->fd[0], cmd->ret);
// printf("open_files : cmd->name = %s | infile = %s | cmd->fd[0] = %d | cmd->ret = %d\n", cmd->name, cmd->infile, cmd->fd[0], cmd->ret);
*/

