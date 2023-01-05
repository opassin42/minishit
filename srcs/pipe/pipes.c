/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:35:41 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/05 19:22:11 by ccouliba         ###   ########.fr       */
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

static int	count_pipe(t_cmd *cmd)
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
	int	i;

	i = 0;
	// signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (i < (count_pipe(cmd) + 1))
	{
		waitpid(g_data.pid, &g_data.status, 0);
		i++;
	}
}

void	p_child(t_env *envp, t_cmd *cmd)
{
	int	i;
	int	pipes[2];

	i = -1;
	while (++i < count_pipe(cmd))
	{
		pipe(pipes);
		g_data.pid = fork();
		if (g_data.pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, sig_handler);
			if (i != 0)
				dup2(cmd->fd_in, STDIN_FILENO);
			if ((i + 1) != count_pipe(cmd))
				dup2(pipes[1], cmd->fd_out);
			close(pipes[0]);
			close(pipes[1]);
			dup2(pipes[0], cmd->fd_in);
			dup2(pipes[1], cmd->fd_out);
			if ((!cmd->infile || !cmd->outfile))
			{
				g_data.status = execve(cmd->bin, cmd->arg, envp->tab);
				if (g_data.status == -1)
					ft_exit(envp, cmd);
			}
			exit(g_data.status);
		}
		close(pipes[1]);
		close(pipes[0]);
		dup2(pipes[0], cmd->fd_in);
	}
}
