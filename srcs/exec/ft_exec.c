/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:48:13 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/20 01:14:48 by ccouliba         ###   ########.fr       */
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
		if (!access(bin, F_OK | R_OK | X_OK))
			return (bin);
	}
	return (bin);
}

static char	*binary_file(t_cmd *cmd, char **path)
{
	if (!path)
		return (NULL);
	if ((*cmd->name == '.' || *cmd->name == '/') && access(cmd->name, F_OK))
		cmd->bin = ft_strdup(cmd->name);
	else
		cmd->bin = bin_path(cmd, path);
	if (!cmd->bin)
		return (NULL);
	return (cmd->bin);
}

/*
** Handle ./.etc and .//etc
** Have to RE-make this function
*/
int	check_for_slash(char *s)
{
	while (*s)
	{
		if (*s != '/' && *s != '.')
			return (EXIT_SUCCESS);
		++s;
	}
	return (EXIT_FAILURE);
}

/*
** Flag existing means there is another char 
*/
void	ft_non_builtin(t_env *envp, t_cmd *cmd, char **path, int i)
{
	(void)envp;
	if (!path)
		ft_exit(envp, cmd);
	cmd->bin = binary_file(cmd, path);
	if (check_cmd(cmd->name))
	{
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		cmd_error(cmd->name, ERRNO_3, 2, ft_putstr_fd);
	}
	else if (!cmd->bin || access(cmd->bin, F_OK | R_OK | X_OK) != 0)
	{
		g_data.status = 127;
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		cmd_error(cmd->name, ERRNO_2, 2, ft_putstr_fd);
	}
	p_child(envp, cmd, i);
}

int	ft_exec(t_env *envp, t_cmd *cmd)
{
	int		i;
	int		ret;
	t_cmd	*temp;

	i = 0;
	ret = 0;
	temp = cmd;
	g_data.max = count_pipe(cmd) + 1;
	while (cmd)
	{
		if (cmd->ret == -1)
			return (EXIT_FAILURE);
		ret = ft_router(envp, cmd, i);
		cmd = cmd->next;
		++i;
	}
	if (temp->id == -1)
		close(temp->fd[0]);
	while (temp)
	{
		if (waitpid(temp->pid, &g_data.status, 0))
			g_data.status = WEXITSTATUS(g_data.status);
		temp = temp->next;
	}
	g_data.prev = -1;
	return (ret);
}
