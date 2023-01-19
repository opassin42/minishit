/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:35:41 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/19 21:29:58 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cmdsize(t_list *cmd)
{
	int	i;

	i = 0;
	if (cmd)
	{
		while (cmd)
		{
			cmd = cmd->next;
			i++;
		}
	}
	return (i);
}

int	count_pipe(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		++i;
		cmd = cmd->next;
	}
	return (i);
}

void	p_father(t_cmd *cmd)
{
	close(cmd->fd[1]);
	if (g_data.prev != -1)
		close(g_data.prev);
	g_data.prev = cmd->fd[0];
	if (waitpid(cmd->pid, &g_data.status, 0))
		g_data.status = WEXITSTATUS(g_data.status);
}

static void	p_child(t_env *envp, t_cmd *cmd, int i)
{
	int		max;

	max = count_pipe(cmd) + 1;
	signal(SIGINT, child_handler);
	signal(SIGQUIT, SIG_DFL);
	if ((i == 0 && max == 2) || (cmd->infile || cmd->outfile))
	{
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		if (execve(cmd->bin, cmd->arg, envp->tab) == -1)
			exit(g_data.status = errno);
	}
	else if (i + 1 != max)
	{
		dup2(cmd->fd[1], STDOUT_FILENO);
		close(cmd->fd[1]);
	}
	else if (i != 0)
	{
		dup2(g_data.prev, STDIN_FILENO);
		close(g_data.prev);
	}
	close(cmd->fd[1]);
	close(cmd->fd[0]);
	if (execve(cmd->bin, cmd->arg, envp->tab) == -1)
		exit(g_data.status = errno);
}

void	ft_pipe(t_env *envp, t_cmd *cmd, int i)
{
	p_child(envp, cmd, i);
	p_father(cmd);
	close(cmd->fd[0]);
	return ;
}
