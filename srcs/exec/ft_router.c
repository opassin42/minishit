/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_router.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:49:33 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/10 23:52:37 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_init_t_builtin(t_builtin *builtin)
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

static int	ft_builtin_ret(t_env *envp, t_cmd *cmd, t_builtin *builtin, int i)
{
	int	res;

	printf("%d\n", i);
	res = builtin[i].f(envp, cmd);
	return (res);
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

int	ft_router(t_env *envp, t_cmd *cmd)
{
	int			id;
	char		**path;
	t_builtin	builtin[7];
	int			prevfd;
	int			i;

	prevfd = -1;
	i = 0;
	while (i <= count_pipe(cmd))
	{
		ft_init_t_builtin(builtin);
		id = which_builtin(builtin, cmd);
		if (i > 0) // si c'est la 2eme cmd on sauve le out precedent.
		{
			prevfd = cmd->fd[1];
			if (pipe(cmd->fd) == -1) // 
			return (error_pid(prevfd, cmd), errno);
		}
		if (id == -1)
			cmd->pid = fork();
		if (cmd->pid < 0)
			return (error_pid(prevfd, cmd), errno);
		if (cmd->pid == 0)
		{
			printf("child\n");
			if (id == -1)
			{
				path = path_in_env(envp, "PATH"); 
				if (!path)
					return (-1);
				printf("ft_non_builtin\n");
				ft_non_builtin(envp, cmd, path, prevfd, i, id);//prevfd = cmd->fd[1] ?
			}
			else
			{
				printf("ft_builtin_ret\n");
				exit(ft_builtin_ret(envp, cmd, builtin, id));
			}
		}
		else
			if (pid_father(cmd, &prevfd, i) == -1)
				return (EXIT_FAILURE);
		if (!cmd->next)
			break;
		cmd = cmd->next;
		++i;
	}
	ft_waitpid(cmd->pid, cmd);// in pid_fath???
	return (g_data.status);
}
