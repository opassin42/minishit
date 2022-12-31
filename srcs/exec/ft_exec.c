/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:48:13 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/31 11:45:45 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	if (*cmd->name == '.' || *cmd->name == '/')
		return (cmd->name);
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
	if ((*cmd->name == '.' || *cmd->name == '/') && access(cmd->name, F_OK))
		cmd->bin = cmd->name;
	else
		cmd->bin = bin_path(cmd, path);
	if (!cmd->bin)
		return (NULL);
	return (cmd->bin);
}

static int	check_cmd(t_cmd *cmd)
{
	if ((*cmd->name == '.') && ft_strlen(cmd->name) < 2)
		return (EXIT_FAILURE);
	if (*cmd->name == '.' || *cmd->name == '/')
	{
		if (*cmd->name == '/' && ft_strlen(cmd->name) < 2)
			return (EXIT_FAILURE);
		if (*(cmd->name + 1))
		{
			if (*(cmd->name + 1) == '.' || *(cmd->name + 1) == '/')
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_non_builtin(t_env *envp, t_cmd *cmd, char **path)
{
	(void)envp;
	if (!path)
		return (EXIT_FAILURE);
	cmd->bin = binary_file(cmd, path);
	if (!cmd->bin || check_cmd(cmd)
		|| access(cmd->bin, F_OK | R_OK | X_OK) != 0)
		return (cmd_error(cmd->name, ERRNO_2, 2, ft_putstr_fd), 127);
	p_child(envp, cmd);
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
	int	ret;

	ret = 0;
	while (cmd)
	{
		ret = ft_router(envp, cmd);
		cmd = cmd->next;
	}
	return (ret);
}
