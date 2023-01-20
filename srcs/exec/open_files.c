/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 05:04:34 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/20 19:04:09 by ccouliba         ###   ########.fr       */
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
					exec_error((char *)tmp->next->val, ERRNO_3, 2,
						ft_putstr_fd);
			if (fd == -1)
			{
				g_data.rd_error = 1;
				return ;
			}
		}
	}
}

static void	open_infiles(t_cmd *cmd)
{
	cmd->fd[0] = open(cmd->infile, O_RDONLY, 0666);
	if (cmd->fd[0] == -1)
	{
		exec_error((char *)cmd->infile, ERRNO_3, 2, ft_putstr_fd);
	}
	exit(g_data.status);
}

static void	open_outfiles(t_cmd *cmd)
{
	if (!cmd->append)
		cmd->fd[1] = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		cmd->fd[1] = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (cmd->fd[1] == -1)
	{
		exec_error((char *)cmd->outfile, ERRNO_4, 2, ft_putstr_fd);
	}
	exit(g_data.status);
}

void	open_files(t_cmd *cmd)
{
	t_rd	*rd;

	rd = cmd->rd;
	while (rd)
	{
		if (rd->flag == 1 || rd->flag == 2)
		{
			cmd->outfile = rd->file;
			if (rd->flag == 2)
				cmd->append = 1;
			else
				cmd->append = 0;
			open_outfiles(cmd);
		}
		else if (rd->flag == 3)
		{
			cmd->infile = rd->file;
			open_infiles(cmd);
		}
		rd = rd->next;
	}
}

/*
// printf("open_files : cmd->name = %s | outfile = %s | cmd->fd[1] = %d | cmd->ret = %d\n", cmd->name, cmd->outfile, cmd->fd[1], cmd->ret);
// printf("open_files : cmd->name = %s | outfile = %s | cmd->fd[1] = %d | cmd->ret = %d\n", cmd->name, cmd->outfile, cmd->fd[1], cmd->ret);
// printf("open_files : cmd->name = %s | infile = %s | cmd->fd[0] = %d | cmd->ret = %d\n", cmd->name, cmd->infile, cmd->fd[0], cmd->ret);
// printf("open_files : cmd->name = %s | infile = %s | cmd->fd[0] = %d | cmd->ret = %d\n", cmd->name, cmd->infile, cmd->fd[0], cmd->ret);
*/
