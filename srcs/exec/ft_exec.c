/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:48:13 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/15 01:06:41 by ccouliba         ###   ########.fr       */
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

int	ft_non_builtin(t_env *envp, t_cmd *cmd, char **path)
{
	if (!path)
		return (EXIT_FAILURE);
	cmd->bin = binary_file(cmd, path);
	if (!cmd->bin)
		return (cmd_error(cmd->name, ERRNO_2, 2, ft_putstr_fd), EXIT_FAILURE);
	if (access(cmd->bin, F_OK))
		return (cmd_error(cmd->name, ERRNO_2, 2, ft_putstr_fd),
			g_data.status = 127);
	g_data.pid = fork();
	if (g_data.pid == -1)
		return (EXIT_FAILURE);
	else if (g_data.pid == 0)
	{
		signal(SIGQUIT, sig_handler);
		g_data.status = execve(cmd->bin, cmd->arg, envp->tab);
		if (g_data.status == -1)
			perror((const char *)cmd->name);
		exit(g_data.status);
	}
	else
	{
		waitpid(g_data.pid, &g_data.status, 0);
		if (signal(SIGQUIT, sig_handler))
		{
			ft_putstr_fd("Quit: (core dump)\n", 2);
			return (g_data.status = 131);
		}
		// if (g_data.sigint || g_data.sigquit)
		// 	return (g_data.status);
	}
	if (g_data.status == 512 || g_data.status == 256)
		g_data.status = g_data.status / 256;
	return (g_data.status);
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
	int	status;

	status = 0;
	while (cmd)
	{
		status = ft_router(envp, cmd);
		cmd = cmd->next;
	}
	return (status);
}
