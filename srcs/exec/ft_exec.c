/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:48:13 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/28 05:20:06 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

<<<<<<< HEAD
static char	*bin_path(t_cmd *cmd, char **path)
{
	int		i;
	char	*bin;
	char	*tmp;

	if (!path)
		return (NULL);
	i = -1;
	bin = NULL;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return (NULL);
		bin = ft_strjoin(tmp, cmd->name);
		if (!bin)
			return (NULL);
		if (!access(bin, F_OK))// && !access(cmd->bin, R_OK))
			return (bin);
	}
	return (bin);
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
	cmd->bin = bin_path(cmd, path);
	printf("-> [bin_path : %s]\n", cmd->bin);
	if (!cmd->bin)
		return (EXIT_FAILURE);
	ret = fork();
	if (ret == -1)
		return (EXIT_FAILURE);
	if (ret == 0)
	{
		printf ("\t-> IN CHILD PROCESS <-\n");
		if (access(cmd->bin, F_OK) != 0)
			return (printf("minishell : %s: command not found\n", cmd->name), 1);
		if (execve(cmd->bin, cmd->arg, envp->tab) == -1)
			perror((const char *)cmd->name);
		return (EXIT_SUCCESS);
	}
	else
		wait(NULL);
	return (EXIT_SUCCESS);
}

void	ft_exec(t_env *envp, t_cmd *cmd)
{
	while (cmd)
	{
		ft_router(envp, cmd);
		cmd = cmd->next;
	}
	return ;
}
