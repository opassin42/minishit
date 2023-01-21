/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 05:04:34 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/21 13:16:51 by ccouliba         ###   ########.fr       */
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

void	rd_error(t_cmd *cmd)
{
	if (errno == 13)
		printf("minishell: %s:: %s\n", cmd->name, ERRNO_4);
	else
		printf("minishell: %s:: %s\n", cmd->name, ERRNO_6);
	close(g_data.pfd[1]);
	close(g_data.pfd[0]);
	exit(g_data.status);
}

void	open_files(t_cmd *cmd)
{
	int		fd;
	t_rd	*rd;

	rd = cmd->rd;
	fd = -1;
	while (rd)
	{
		if (rd->flag == 1)
			fd = open(rd->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (rd->flag == 2)
			fd = open(rd->file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (rd->flag == 3)
			fd = open(rd->file, O_RDONLY);
		if (fd == -1)
		{
			g_data.status = 1;
			rd_error(cmd);
		}
		if (rd->flag == 3)
			dup2(fd, STDIN_FILENO);
		if (rd->flag != 3)
			dup2(fd, STDOUT_FILENO);
		close(fd);
		rd = rd->next;
	}
}
