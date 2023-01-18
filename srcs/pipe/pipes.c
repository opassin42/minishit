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

void	p_father(t_cmd *cmd, int prev)
{
	(void)prev;
// 	int	i;

// 	i = 0;
	// while (i < (count_pipe(cmd) + 1))
	// {
		waitpid(cmd->pid, &g_data.status, 0);
		// i++;
	// }
	// close(prev);
}

void	p_child(t_env *envp, t_cmd *cmd, int i, int prev)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_DFL);

	if (i != 0)
	{
		if (i != (count_pipe(cmd) - 1))
		{
			dup2(cmd->fd[1], STDOUT_FILENO);
		}
		dup2(prev, STDIN_FILENO);
		close(prev);
	}
	//redir
	printf("cmd = %s | fdin = %d | fdout = %d\n", cmd->name, cmd->fd[0], cmd->fd[1]);
	if (cmd->fd[1] != STDOUT_FILENO)
		close(cmd->fd[1]);
	if (cmd->fd[0] != STDIN_FILENO)
		close(cmd->fd[0]);
	g_data.status = execve(cmd->bin, cmd->arg, envp->tab);
	if (g_data.status == -1)
			ft_exit(envp, cmd);
	exit(g_data.status);
}
/*
void	p_child(t_env *envp, t_cmd *cmd, int i, int fd_in)
{
	// int	i;
	// int	pipes[2];

	// i = -1;
	// while (++i < count_pipe(cmd))
	// {
	// 	pipe(pipes);
	// 	cmd->pid = fork();
	// 	if (cmd->pid == 0)
	// 	{
			signal(SIGINT, sig_handler);
			signal(SIGQUIT, SIG_DFL);
			if (i != 0)
				dup2(cmd->fd[0], STDIN_FILENO);
			if ((i + 1) != count_pipe(cmd))
			{
				dup2(fd_in, cmd->fd[1]);
				return ;
			}// close(pipes[0]);
			// close(pipes[1]);
			// dup2(pipes[0], cmd->fd[0]);
			// dup2(pipes[1], cmd->fd[1]);
			if ((!cmd->infile || !cmd->outfile))
			{
				g_data.status = execve(cmd->bin, cmd->arg, envp->tab);
				if (g_data.status == -1)
					ft_exit(envp, cmd);
			}
			exit(g_data.status);
		// }
		// close(pipes[1]);
		// // close(pipes[0]);
		// dup2(pipes[0], cmd->fd[0]);
		// close(pipes[0]);
	// }
}
*/