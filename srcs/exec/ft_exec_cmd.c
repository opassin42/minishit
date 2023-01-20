/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:49:33 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/20 09:45:09 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static void	exec_builtin(t_env *envp, t_cmd *cmd, t_builtin *builtin, int i)
{
	int	res;

	res = builtin[i].f(envp, cmd);
	g_data.status = res;
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

static void	router(t_env *envp, t_cmd *cmd, t_builtin *builtin, int i)
{
	char	**path;

	if (cmd->id == -1)
	{
		path = path_in_env(envp, "PATH");
		if (!path)
			return ;
		ft_non_builtin(envp, cmd, path, i);
	}
	else
		exec_builtin(envp, cmd, builtin, cmd->id);
}

int	exec_cmd(t_env *envp, t_cmd *cmd, int i)
{
	t_builtin	builtin[7];

	ft_init_builtin(builtin);
	cmd->id = which_builtin(builtin, cmd);
	if (cmd->id == -1 || (count_pipe(cmd) > 1))
	{
		if (pipe(cmd->fd) < 0)
			return (perror("minishell: pipe:"), errno);
		cmd->pid = fork();
		if (cmd->pid < 0)
			return (perror("minishell: fork:"), errno);
		if (cmd->pid == 0)
		{
			router(envp, cmd, builtin, i);
			ft_exit(envp, cmd);
		}
		else
			p_father(cmd);
	}
	else if (g_data.max == 1)
		exec_builtin(envp, cmd, builtin, cmd->id);
	return (g_data.status);
}
