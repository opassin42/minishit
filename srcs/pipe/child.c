#include "../../include/minishell.h"

static int	excmd_first(t_cmd *cmd, t_env *envp)
{
	int		fd;

	close(cmd->fd[0]);
	fd = open(cmd->infile, O_RDONLY);
	if (fd == -1)
		return (close(cmd->fd[1]), perror("open"), -1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(cmd->fd[1]), close(fd), perror("dup2"), -1);
	close(fd);
	if (dup2(cmd->fd[1], STDOUT_FILENO) == -1)
		return (close(cmd->fd[1]), perror("dup2"), -1);
	close(cmd->fd[1]);
	if (execve(cmd->bin, cmd->arg, envp->tab) == -1)
		return (perror(""), -1);
	return (0);
}

static int	excmd_between(t_cmd *cmd, t_env *envp, int prevfd)
{
	close(cmd->fd[0]);
	if (dup2(prevfd, STDIN_FILENO) == -1)
		return (close(prevfd), close(cmd->fd[1]), perror("dup2"), -1);
	close(prevfd);
	if (dup2(cmd->fd[1], STDOUT_FILENO) == -1)
		return (close(cmd->fd[1]), perror("dup2"), -1);
	close(cmd->fd[1]);
	if (execve(cmd->bin, cmd->arg, envp->tab) == -1)
		return (perror("execve"), -1);
	return (0);
}

static int	excmd_last(t_cmd *cmd, t_env *envp, int prevfd)
{
	int		fd;

	fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (close(prevfd), -1);
	if (dup2(prevfd, STDIN_FILENO) == -1)
		return (close(prevfd), close(fd), perror("dup2"), -1);
	close(prevfd);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), perror("dup2"), -1);
	close(fd);
	if (execve(cmd->bin, cmd->arg, envp->tab) == -1)
		return (perror("execve"), -1);
	return (0);
}

int	pid_child(t_cmd *cmd, t_env *envp, int prevfd, int i, int id)
{
	if (id != -1)
		return (close(cmd->fd[0]), close(cmd->fd[1]), 0);
	if (i == 0)
	{
		if (!cmd->bin)
			return (close(cmd->fd[0]), close(cmd->fd[1]), exit(127), -1);
		excmd_first(cmd, envp);
		exit (127);
	}
	else if (i == (count_pipe(cmd) - 1))
	{
		if (!cmd->bin)
			return (close(prevfd), exit (127), -1);
		excmd_last(cmd, envp, prevfd);
		exit (127);
	}
	else
	{
		if (!cmd->bin )
			return (close(prevfd), close(cmd->fd[0]),
				close(cmd->fd[1]), exit(127), -1);
		excmd_between(cmd, envp, prevfd);
		exit (127);
	}
}