/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:56:53 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/23 19:22:27 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	excmd_between(t_cmd *cmd, t_env *envp, int prevfd)
{
	close(cmd->fd[1]);
	if (dup2(prevfd, STDIN_FILENO) == -1)
		return (close(prevfd), close(cmd->fd[1]), perror("bettzen dup2"), -1);
	close(prevfd);
	if (dup2(cmd->fd[1], STDOUT_FILENO) == -1)
		return (close(cmd->fd[1]), perror("dup2"), -1);
	close(cmd->fd[1]);
	if (execve(cmd->bin, cmd->arg, envp->tab) == -1)
		return (perror("execve"), -1);
	return (0);
}

static int	excmd_last(t_cmd *cmd, t_env *envp, int prevfd)
{
	int		fd;

	fd = 1;
	if (fd < 0)
		return (close(prevfd), -1);
	if (dup2(prevfd, STDIN_FILENO) == -1)
		return (close(prevfd), close(fd), perror("dup2"), -1);
	close(prevfd);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), perror("last: dup2"), -1);
	if (execve(cmd->bin, cmd->arg, envp->tab) == -1)
		return (perror("execve"), exit(g_data.status), -1);
	return (0);
}

int	pid_child(t_cmd *cmd, t_env *envp, int prevfd, int i, int id)
{
	if (id != -1)
		return (close(cmd->fd[0]), close(cmd->fd[1]), 0);
	if (i == 0 || i == (count_pipe(cmd)))
	{
		if (!cmd->name)
			return (close(cmd->fd[0]), close(cmd->fd[1]), exit(127), -1);
		if (i == 0)
			prevfd = 0;
		return (exit(excmd_last(cmd, envp, prevfd)), 0);
	}
	else
	{
		if (!cmd->bin )
			return (close(prevfd), close(cmd->fd[0]),
				close(cmd->fd[1]), exit(127), -1);
		excmd_between(cmd, envp, prevfd);
		exit (127);
	}
}