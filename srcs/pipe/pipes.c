/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:35:41 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/31 00:07:31 by opassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
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

int ft_wait_procs(int ac, pid_t *list)
{
	int i;
	pid_t w;

	i = 0;
	while (i < ac)
	{
		w = waitpid(list[i], &g_data.status, 0);
		printf("status = %d\n", g_data.status);
		if (w == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(g_data.status))
			printf("terminé, code=%d\n", WEXITSTATUS(g_data.status));
		else if (WIFSIGNALED(g_data.status))
			printf("tué par le signal %d\n", WTERMSIG(g_data.status));
		else if (WIFSTOPPED(g_data.status))
			printf("arrêté par le signal %d\n", WSTOPSIG(g_data.status));
		else if (WIFCONTINUED(g_data.status))
			printf("relancé\n");
		i++;
	}
	return (0);
}


int ft_close_pipes(int **pipefd, int nb_pipes)
{
	int i;

	i = 0;
	while (i < nb_pipes)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
	return (0);
}

int ft_handle_pipe(int **pipefd, int pipes_left, int nb_pipes, int *fd_in)
{
	int fd_out;

	if (pipes_left != nb_pipes)
	{
		ft_putstr_fd("DUP 2 TOKEN = 1IN\n", 2);
		*fd_in = dup2(pipefd[nb_pipes - pipes_left - 1][0], STDIN_FILENO);
		if (*fd_in == -1)
			return (ft_putstr_fd("FD_ERR\n", 2), ft_close_pipes(pipefd, nb_pipes),
					free_pipe_array(pipefd, nb_pipes), EXIT_FAILURE);
		else
			close(pipefd[nb_pipes - pipes_left - 1][0]);
	}
	if (pipes_left != 0)
	{
		ft_putstr_fd("DUP 2 TOKEN = 1OUT\n", 2);
		printf("nb_pipes: %d, pipes_left: %d\n", nb_pipes, pipes_left);
		fd_out = dup2(pipefd[nb_pipes - pipes_left][1], STDOUT_FILENO);
		if (fd_out == -1)
			return (ft_putstr_fd("FD_ERR\n", 2), ft_close_pipes(pipefd, nb_pipes),
					close(*fd_in), free_pipe_array(pipefd, nb_pipes), EXIT_FAILURE);
		else
			close(pipefd[nb_pipes - pipes_left][1]);
	}
	return (fd_out);
}

int **create_pipe_arr(int nb_pipes)
{
	int i;
	int **pipefd;
	// int ret;

	pipefd = (int **)push_top(&g_data.gc ,nb_pipes * sizeof(int*));
	if (pipefd == NULL)
		return (NULL);
	i = -1;
	while (++i < nb_pipes)
	{
		pipefd[i] = (int *)push_top(&g_data.gc, sizeof(int));
		if (pipefd[i] == NULL)
			return (gc_free(), NULL);
	}
	i = -1;
			  while (++i < nb_pipes)
			  {
			  ret = pipe(pipefd[i]);
			  if (ret == -1)
			  return (ft_close_pipes(pipefd, i), NULL);
			  }
	return (pipefd);
}

static void  free_pipe_array(int **pipefd, int nb_pipes)
{
	int i;

	if (!pipefd)
		return ;
	i = -1;
	while (++i < nb_pipes)
	{
		if (!pipefd[i])
			return ;
		free(pipefd[i]);
	}
	free(pipefd);
}


void   ft_pipes(t_env *envp, t_cmd *cmd, int nb_pipes)
{
	int   **pipefd;
	int   i;
	pid_t pidlist[nb_pipes + 1];
	int   pipes_left;
	int   fd_in;

	pipefd = create_pipe_arr(nb_pipes);
	pipes_left = nb_pipes;
	i = 0;
	printf("nb pipes = %d\n", nb_pipes);
	if (nb_pipes == 0)
		printf("no pipe\n");
	if (!pipefd){
		perror("malloc fail");
		exit (EXIT_FAILURE);
	}
	while (cmd)
	{
		if (pipe(pipefd[i]) == -1)
		{
			printf("error create pipe\n");
			exit (EXIT_FAILURE);
		}
		pidlist[i] = fork();
		if (pidlist[i] == 0)
		{
			ft_handle_pipe((int **)pipefd, pipes_left, nb_pipes, &fd_in);
			ft_close_pipes((int **)pipefd, nb_pipes);
			g_data.status = execve(cmd->bin, cmd->arg, envp->tab);
			if (g_data.status == -1)
				ft_exit(envp, cmd);
		}
		i++;
		pipes_left--;
		cmd = cmd->next;
	}
	ft_close_pipes((int **)pipefd, nb_pipes);
	free_pipe_array(pipefd, nb_pipes);
	ft_wait_procs(i, pidlist);
	exit(0);
}
*/