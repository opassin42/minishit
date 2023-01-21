/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:21:28 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/21 03:52:15 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cmd_index(t_cmd **cmd)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = *cmd;
	while (tmp)
	{
		tmp->i = i;
		tmp = tmp->next;
		++i;
	}
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

char	*binary_file(t_cmd *cmd, char **path)
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

int	check_cmd(char *s)
{
	int		flag;
	char	*tmp;

	flag = 0;
	tmp = s;
	if (*s == '.' && ft_strlen(s) == 1)
		return (g_data.status = 2, EXIT_FAILURE);
	while (*s)
	{
		if (*s != '.' && *s != '/')
		{
			flag = 1;
			break ;
		}
		++s;
	}
	if (!flag)
	{
		if (ft_strchr(tmp, '/'))
			return (g_data.status = 126, EXIT_FAILURE);
		return (g_data.status = 127, EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	exec_error(char *token, char *err_msg, int fd, void (*f)())
{
	f("minishell: ", fd);
	f(token, fd);
	f(": ", fd);
	f(err_msg, fd);
	f("\n", fd);
	exit(g_data.status);
}
