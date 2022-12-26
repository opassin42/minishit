/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:48:13 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/26 15:47:18 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cmd_error(char *token, char *err_msg, int fd, void (*f)())
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
			return (gc_free(), NULL);
		bin = ft_strjoin(tmp, cmd->name);
		if (!bin)
			return (gc_free(), NULL);
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

int	ft_non_builtin(t_env *envp, t_cmd *cmd, char **path)
{
	//int	ret;

	if (!path)
		return (EXIT_FAILURE);
	cmd->bin = binary_file(cmd, path);
	if (!cmd->bin)
		return (cmd_error(cmd->name, ERRNO_2, 2, ft_putstr_fd), EXIT_FAILURE);
	if (access(cmd->bin, F_OK))
		return (127);
//		return (cmd_error(cmd->name, ERRNO_2, 2, ft_putstr_fd), 127);
	p_child(envp, cmd);
	/*remplacer creation child
	ret = fork();
	if (ret == -1)
		return (EXIT_FAILURE);
	if (ret == 0)
	{
		if (execve(cmd->bin, cmd->arg, envp->tab) == -1)
			return (perror((const char *)cmd->name), EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	else
	{
		wait(&ret);
		return (errno);
	}*/
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
