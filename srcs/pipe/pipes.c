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

int count_pipe(t_cmd *cmd)
{
  int i;

  i = -1;
  while (cmd)
  {
    ++i;
    cmd = cmd->next;
  }
  return (i);
}

void  error_pid(int prevfd, t_cmd *cmd)
{
  if (prevfd)
    close(prevfd);
  if (cmd->fd)
  {
    close(cmd->fd[0]);
    close(cmd->fd[1]);
  }
  perror("error_pid");
}

void  error_pipe(int prevfd)
{
  if (prevfd)
    close(prevfd);
  perror("error_pipe");
}


int   ft_fork(int *prevfd, t_cmd *cmd)
{
  cmd->pid = fork();
  if (cmd->pid < 0)
  {
    error_pid(*prevfd, cmd);
    g_data.status = errno;
    return (-1);
  }
  return (0);
}

int ft_waitpid(int pid_last, t_cmd *cmd)
{
	int i;
	int status;
	int w;

	i = 0;
	while (i <= count_pipe(cmd))
	{
			w = waitpid(pid_last, &status, 0);
			if (w == -1)
			{
				perror("waitpid");
				exit(EXIT_FAILURE);
			}
			// if (WIFEXITED(status))
			// 	return(WEXITSTATUS(status));
			// else if (WIFSIGNALED(status))
			// 	return(WTERMSIG(status));
			// else if (WIFSTOPPED(status))
			// 	return(WSTOPSIG(status));
			// else if (WIFCONTINUED(status))
			// 		printf("continue\n");
			cmd = cmd->next;
			i++;
	}
	return (0);
}