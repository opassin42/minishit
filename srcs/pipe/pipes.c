/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:35:41 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/17 19:27:23 by ccouliba         ###   ########.fr       */
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
	g_data.prev = cmd->fd[1];
	waitpid(cmd->pid, &g_data.status, 0);
}

void	p_child(t_env *envp, t_cmd *cmd, int i)
{
	int		max;

	max = count_pipe(cmd) + 1;
	signal(SIGINT, child_handler);
	signal(SIGQUIT, SIG_DFL);
	if ((i == 0 && max == 2) || (cmd->infile || cmd->outfile))
	{
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		g_data.status = execve(cmd->bin, cmd->arg, envp->tab);
	}
	if (i + 1 != max)
		dup2(cmd->fd[1], STDOUT_FILENO);
	if (i != 0)
	{
		dup2(g_data.prev, STDIN_FILENO);
		close(g_data.prev);
	}
	close(cmd->fd[1]);
	close(cmd->fd[0]);
	g_data.status = execve(cmd->bin, cmd->arg, envp->tab);
}
