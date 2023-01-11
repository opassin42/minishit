#include "../../include/minishell.h"

int pid_father(t_cmd *cmd, int *prevfd, int i)
{
/*	printf("i = %d\n", i);
	if (i == 0)
	{
		*prevfd = dup(cmd->fd[0]);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		if (*prevfd == -1)
			return (perror("dup"), errno);
	}
	else */
	if (i == count_pipe(cmd))
	{
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		if (*prevfd != 0)
			close(*prevfd);
	}
	else
	{
		if (*prevfd != 0)
			close(*prevfd);
		*prevfd = dup(cmd->fd[0]);
		// close(cmd->fd[0]);
		// close(cmd->fd[1]);
		if (*prevfd == -1)
			return (perror("dup"), errno);
	}
	return (0);
}
