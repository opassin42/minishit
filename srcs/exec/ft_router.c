/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_router.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:49:33 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/13 20:19:47 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_init_builtin(t_builtin *builtin)
{
	builtin[0].key = "echo";
	builtin[0].f = ft_echo;
	builtin[1].key = "env";
	builtin[1].f = ft_env;
	builtin[2].key = "pwd";
	builtin[2].f = ft_pwd;
	builtin[3].key = "cd";
	builtin[3].f = ft_cd;
	builtin[4].key = "unset";
	builtin[4].f = ft_unset;
	builtin[5].key = "export";
	builtin[5].f = ft_export;
	builtin[6].key = "exit";
	builtin[6].f = ft_exit;
}

static int	which_builtin(t_builtin *builtin, t_cmd *cmd)
{
	int	i;
	int	cmp;

	i = -1;
	while (++i < 7)
	{
		cmp = ft_strcmp(builtin[i].key, cmd->name);
		if (!cmp)
			return (i);
	}
	return (-1);
}

static int	exec_builtin(t_env *envp, t_cmd *cmd, t_builtin *builtin, int i)
{
	int	res;

	res = builtin[i].f(envp, cmd);
	return (res);
}

static char	**path_in_env(t_env *envp, char *var_name)
{
	char	*value;
	char	**path;

	if (!var_name)
		return (NULL);
	value = find_value(envp, var_name);
	if (!value)
		return (NULL);
	path = ft_split(value, ':');
	if (!path)
		return (NULL);
	return (path);
}

int	ft_router(t_env *envp, t_cmd *cmd, int i, int prev)
{
	int			id;
	int			status;
	char		**path;
	t_builtin	builtin[7];

	ft_init_builtin(builtin);
	id = which_builtin(builtin, cmd);
	if (id == -1 || (count_pipe(cmd) > 1))
	{
		if (pipe(cmd->fd) < 0)
			return (perror("minishell: pipe:"), errno);
		cmd->pid = fork();
		if (cmd->pid < 0)
			return (perror("minishell: fork:"), errno);
		if (cmd->pid == 0)
		{
			if (id == -1)
			{
				path = path_in_env(envp, "PATH");
				if (!path)
					return (-1);
				status = ft_non_builtin(envp, cmd, path, i, prev);
				if (status == 127)
					exit(status);
			}
			else
				exit(exec_builtin(envp, cmd, builtin, id));
		}
		else
			p_father(cmd, prev);
	}
	else if (count_pipe(cmd) == 1)
	{
		status = exec_builtin(envp, cmd, builtin, id);
		p_father(cmd, prev);
	}
	if (g_data.sigint == 1 || g_data.sigquit == 1)
		return (g_data.status);
	if (g_data.status == 512 || g_data.status == 256)
			status = g_data.status / 256;
	return (status);
}
