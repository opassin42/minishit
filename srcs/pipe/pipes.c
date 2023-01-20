/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:35:41 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/20 23:55:40 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cmdsize(t_cmd *cmd)
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

	i = -1;
	while (cmd)
	{
		++i;
		cmd = cmd->next;
	}
	return (i);
}

void	p_father(t_cmd *cmd)
{
	(void)cmd;
	close(g_data.pfd[1]);
	if (g_data.prev != -1)
		close(g_data.prev);
	g_data.prev = g_data.pfd[0];
	return ;
}

void	p_child(t_env *envp, t_cmd *cmd)
{
	signal(SIGINT, child_handler);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->i != g_data.cmdsize - 1)
		dup2(g_data.pfd[1], STDOUT_FILENO);
	if (cmd->i != 0)
	{
		dup2(g_data.prev, STDIN_FILENO);
		close(g_data.prev);
	}
	close(g_data.pfd[0]);
	close(g_data.pfd[1]);
	if (cmd->id == -1)
		if (execve(cmd->bin, cmd->arg, envp->tab) == -1)
			exit(g_data.status = errno);
	exit(g_data.status = errno);
}

void	ft_waitpid(t_cmd *cmd)
{
	if (cmd->id == -1)
		close(g_data.pfd[0]);
	while (cmd)
	{
		waitpid(cmd->pid, &g_data.status, 0);
		g_data.status = WEXITSTATUS(g_data.status);
		if (!cmd->next)
			break ;
		cmd = cmd->next;
	}
	g_data.prev = -1;
}
