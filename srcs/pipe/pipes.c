/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:35:41 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/28 21:19:46 by ccouliba         ###   ########.fr       */
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
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
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
			signal(SIGINT, sig_handler);
			signal(SIGQUIT, SIG_DFL);
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

/*
*******************************************************************************
**** Pipe and fork reworking for more efficience
*******************************************************************************
*/
// int	ft_cmd_size(t_cmd *cmd)
// {
// 	int	i;

// 	i = 0;
// 	if (cmd)
// 	{
// 		while (cmd)
// 		{
// 			cmd = cmd->next;
// 			i++;
// 		}
// 	}
// 	return (i);
// }

// void	p_father(t_cmd *cmd, int *pipes)
// {
// 	waitpid(g_data.pid, &g_data.status, 0);
// 	close(pipes[1]);
// 	dup2(cmd->fd_out, STDOUT_FILENO);
// 	dup2(pipes[0], STDIN_FILENO);
// 	close(cmd->fd_out);
// }

// void	p_child(t_env *envp, t_cmd *cmd, int *pipes)
// {
// 	dup2(cmd->fd_in, STDIN_FILENO);
// 	if (cmd->next)
// 		dup2(pipes[1], STDOUT_FILENO);
// 	close(pipes[0]);
// 	close(cmd->fd_in);
// 	g_data.status = execve(cmd->bin, cmd->arg, envp->tab);
// 	if (g_data.status == -1)
// 		ft_exit(envp, cmd);
// 	exit(g_data.status);
// }

// void	process(t_env *envp, t_cmd *cmd)
// {
// 	int	pipes[2];

// 	pipe(pipes);
// 	while (cmd)
// 	{
// 		g_data.pid = fork();
// 		if (g_data.pid == -1)
// 			return ;
// 		if (g_data.pid == 0)
// 			p_child(envp, cmd, pipes);
// 		else
// 			p_father(cmd, pipes);
// 		cmd = cmd->next;
// 	}
// }

/*
*** WLTY
*/
void	parent(int fd_in, t_cmd *cmd)
{
	int	i;

	i = 0;
	close(fd_in);
	while (i < (count_pipe(cmd) + 1))
	{
		waitpid(g_data.pid, &g_data.status, 0);
		i++;
	}
}

void	close_pipe_fd(int *pipes)
{
	close(pipes[0]);
	close(pipes[1]);
}

void	children(t_env *envp, t_cmd *cmd, int fd_in)
{
	int	i;
	int	pipes[2];

	i = 0;
	while (i < (count_pipe(cmd) + 1))
	{
		pipe(pipes);
		g_data.pid = fork();
		if (g_data.pid == 0)
		{
			if (i != 0)
				dup2(fd_in, STDIN_FILENO);
			if ((i + 1) != (count_pipe(cmd) + 1))
				dup2(pipes[1], STDOUT_FILENO);
			close_pipe_fd(pipes);
			close(fd_in);
			if (!cmd->infile || !cmd->outfile)
			{
				g_data.status = execve(cmd->bin, cmd->arg, envp->tab);
				if (g_data.status == -1)
					ft_exit(envp, cmd);
			}
			exit(0);
		}
		dup2(pipes[0], cmd->fd_in);
		close_pipe_fd(pipes);
		i++;
	}
}

void	ft_pipex(t_env *envp, t_cmd *cmd)
{
	int		fd_in;

	fd_in = dup(STDIN_FILENO);
	children(envp, cmd, fd_in);
	parent(fd_in, cmd);
}
