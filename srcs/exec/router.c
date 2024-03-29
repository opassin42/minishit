/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:24:05 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/21 13:27:47 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static void	exec_non_builtin(t_env *envp, t_cmd *cmd)
{
	char	**path;

	path = path_in_env(envp, "PATH");
	if (!path)
		return ;
	cmd->bin = binary_file(cmd, path);
	if (check_cmd(cmd->name))
	{
		close(g_data.pfd[0]);
		close(g_data.pfd[1]);
		exec_error(cmd->name, ERRNO_3, 2, ft_putstr_fd);
	}
	else if (!cmd->bin || access(cmd->bin, F_OK | R_OK | X_OK) != 0)
	{
		g_data.status = 127;
		close(g_data.pfd[0]);
		close(g_data.pfd[1]);
		exec_error(cmd->name, ERRNO_2, 2, ft_putstr_fd);
	}
	p_child(envp, cmd);
}

int	which_builtin(t_builtin *builtin, t_cmd *cmd)
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

void	exec_builtin(t_env *envp, t_cmd *cmd, t_builtin *builtin)
{
	int	fdstd;

	if (g_data.cmdsize > 1 && cmd->i < g_data.cmdsize - 1)
		p_child(envp, cmd);
	fdstd = dup(STDOUT_FILENO);
	if (g_data.cmdsize == 1 || cmd->i == (g_data.cmdsize - 1))
		open_files(cmd);
	g_data.status = builtin[cmd->id].f(envp, cmd);
	dup2(fdstd, STDOUT_FILENO);
	close(fdstd);
	return ;
}

void	router(t_env *envp, t_cmd *cmd, t_builtin *builtin)
{
	if (cmd->id != -1)
		exec_builtin(envp, cmd, builtin);
	else
		exec_non_builtin(envp, cmd);
}
