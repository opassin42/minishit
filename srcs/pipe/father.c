#include "../../include/minishell.h"

int	pid_father(t_cmd *cmd, int *prevfd, int i)
{
	if (i == 0)
	{
				close (cmd->fd[0]);
		close(cmd->fd[1]);
		*prevfd = dup(cmd->fd[0]);
		if (*prevfd == -1)
			return (perror("dup"), errno);
	}
	else if (i == count_pipe(cmd) - 1)
		close(*prevfd);
	else
	{
		close(*prevfd);
		*prevfd = dup(cmd->fd[0]);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		if (*prevfd == -1)
			return (perror("dup"), errno);
	}
	return (0);
}
