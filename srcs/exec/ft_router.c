/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_router.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:49:33 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/20 01:52:19 by ccouliba         ###   ########.fr       */
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

int	ft_router(t_env *envp, t_cmd *cmd, int i)
{
	char		**path;
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
			if (cmd->id == -1)
			{
				path = path_in_env(envp, "PATH");
				if (!path)
					return (-1);
				ft_non_builtin(envp, cmd, path, i);
			}
			else
				exec_builtin(envp, cmd, builtin, cmd->id);
			ft_exit(envp, cmd);
		}
		else
			p_father(cmd);
	}
	else if (g_data.max == 1)
		exec_builtin(envp, cmd, builtin, cmd->id);
	return (g_data.status);
}

void	ft_waitpid(t_cmd *cmd)
{
	if (cmd->id == -1)
		close(cmd->fd[0]);
	while (cmd)
	{
		if (waitpid(cmd->pid, &g_data.status, 0))
			g_data.status = WEXITSTATUS(g_data.status);
		cmd = cmd->next;
	}
	g_data.prev = -1;
}
