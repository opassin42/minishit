/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:48:13 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/18 02:06:06 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	cmd_error(char *token, char *err_msg, int fd, void (*f)())
{
	f("minishell: ", fd);
	f(token, fd);
	f(": ", fd);
	f(err_msg, fd);
	f("\n", fd);
	return ;
}

static char	*bin_path(t_cmd *cmd, char **path)
{
	int		i;
	char	*bin;
	char	*tmp;

	if (!path)
		return (NULL);
	bin = NULL;
	if (!cmd->name || !*cmd->name)
		return (NULL);
	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return (NULL);
		bin = ft_strjoin(tmp, cmd->name);
		if (!bin)
			return (NULL);
		if (!access(bin, F_OK))
			return (bin);
	}
	return (bin);
}

static char	*binary_file(t_cmd *cmd, char **path)
{
	if (!path)
		return (NULL);
	if (!access(cmd->name, F_OK))
		cmd->bin = cmd->name;
	else
		cmd->bin = bin_path(cmd, path);
	return (cmd->bin);
}

/*
** "A NULL argv[0] was passed through an exec system call."
** Have to find where this error above comes from
** check if cmd has param. If not, join cmd->name to a right path
*/
int	ft_non_builtin(t_env *envp, t_cmd *cmd, char **path)
{
	int	ret;

	if (!path)
		return (EXIT_FAILURE);
	cmd->bin = binary_file(cmd, path);
	if (!cmd->bin)
		return (EXIT_FAILURE);
	if (access(cmd->bin, F_OK))
		return (cmd_error(cmd->name, ERRNO_2, 2, ft_putstr_fd), 127);
	ret = fork();
	if (ret == -1)
		return (EXIT_FAILURE);
	if (ret == 0)
	{
		if (execve(cmd->bin, cmd->arg, envp->tab) == -1)
			return (perror((const char *)cmd->name), errno);
		return (EXIT_SUCCESS);
	}
	else
		wait(NULL);
	return (EXIT_SUCCESS);
}

/*
** I have to change SHLVL->value
** Each time i go into another minishell instance
** 
** Something like :
** If (!ft_strcmp(cmd->name, "./minishell"))
** 		->find_in_env(envp, "SHLVL", change_shlvl);
*/
int	ft_exec(t_env *envp, t_cmd *cmd)
{
	int	ret;

	ret = 0;
	while (cmd)
	{
		ret = ft_router(envp, cmd);
		cmd = cmd->next;
	}
	return (ret);
}
