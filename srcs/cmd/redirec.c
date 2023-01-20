/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 05:04:34 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/20 09:19:06 by ccouliba         ###   ########.fr       */
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

static void	rd_in(t_cmd *cmd)
{
	cmd->ret = open(cmd->infile, O_RDONLY, 0666);
	if (cmd->ret == -1)
	{
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		exec_error((char *)cmd->infile, ERRNO_3, 2, ft_putstr_fd);
		exit(errno);
	}
	dup2(cmd->ret, cmd->fd[0]);
	close(cmd->ret);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	exit(g_data.status);
}

static void	rd_out(t_cmd *cmd)
{
	if (!cmd->append)
		cmd->ret = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		cmd->ret = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (cmd->ret == -1)
	{
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		exec_error((char *)cmd->outfile, ERRNO_4, 2, ft_putstr_fd);
		exit(errno);
	}
	dup2(cmd->ret, cmd->fd[1]);
	close(cmd->ret);
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
			printf("open_files : cmd->name = %s | outfile = %s | cmd->fd[1] = %d | cmd->ret = %d\n", cmd->name, cmd->outfile, cmd->fd[1], cmd->ret);
			rd_out(cmd);
			printf("open_files : cmd->name = %s | outfile = %s | cmd->fd[1] = %d | cmd->ret = %d\n", cmd->name, cmd->outfile, cmd->fd[1], cmd->ret);
		}
		else if (rd->flag == 3)
		{
			cmd->infile = rd->file;
			printf("open_files : cmd->name = %s | infile = %s | cmd->fd[0] = %d | cmd->ret = %d\n", cmd->name, cmd->infile, cmd->fd[0], cmd->ret);
			rd_in(cmd);
			printf("open_files : cmd->name = %s | infile = %s | cmd->fd[0] = %d | cmd->ret = %d\n", cmd->name, cmd->infile, cmd->fd[0], cmd->ret);
		}
		rd = rd->next;
	}
}

// void	init_rd(t_cmd *cmd, t_list *token)
// {
// 	if (!ft_strcmp((char *)token->val, "<")
// 		|| !ft_strcmp((char *)token->val, "<<"))
// 	{
// 		cmd->infile = (char *)token->next->val;
// 		if (!ft_strcmp((char *)token->val, "<<"))
// 			cmd->hdoc = 1;
// 		else
// 			cmd->hdoc = 0;
// 		if (rd_in(cmd) != EXIT_SUCCESS)
// 			exec_error((char *)token->next->val, ERRNO_3, 2, ft_putstr_fd);
// 	}
// 	else if (!ft_strcmp((char *)token->val, ">")
// 		|| !ft_strcmp((char *)token->val, ">>"))
// 	{
// 		cmd->outfile = (char *)token->next->val;
// 		if (!ft_strcmp((char *)token->val, ">>"))
// 			cmd->append = 1;
// 		else
// 			cmd->append = 0;
// 		if (rd_out(cmd) != EXIT_SUCCESS)
// 			exec_error((char *)token->next->val, ERRNO_4, 2, ft_putstr_fd);
// 	}
// }

int	define_rd(char *s)
{
	if (!ft_strcmp(s, ">"))
		return (1);
	if (!ft_strcmp(s, ">>"))
		return (2);
	if (!ft_strcmp(s, "<"))
		return (3);
	return (0);
}

t_rd	*ft_new_rd(t_list *token)
{
	t_rd	*rd;

	rd = (t_rd *)push_top(&g_data.gc, sizeof(t_rd));
	if (!rd)
		return (gc_free(), NULL);
	rd->flag = define_rd((char *)token->val);
	token = token->next;
	if (token)
		rd->file = (char *)token->val;
	else
		rd->file = NULL;
	rd->next = NULL;
	return (rd);
}

t_rd	*ft_last_rd(t_rd *rd)
{
	if (rd)
	{
		while (rd->next)
			rd = rd->next;
	}
	return (rd);
}

void	ft_rd_addback(t_rd **rd, t_rd *new_rd)
{
	if (new_rd)
	{
		if (*rd)
			ft_last_rd(*rd)->next = new_rd;
		else
			*rd = new_rd;
	}
}

void	init_rd_struct(t_cmd *cmd, t_list *token)
{
	t_rd	*rd;

	rd = ft_new_rd(token);
	if (!rd)
		return ;
	ft_rd_addback(&cmd->rd, rd);
	// while (cmd->rd)
	// {
	// 	printf("cmd->rd->flag = %d | cmd->rd->file = %s\n", cmd->rd->flag, cmd->rd->file);
	// 	cmd->rd = cmd->rd->next;
	// }
}

