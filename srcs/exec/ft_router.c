/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_router.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:49:33 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/27 20:06:44 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**path_value(t_env *envp, char *var_name)
{
	char	*value;
	char	**path;

	value = find_value(envp, var_name);
	if (!value)
		return (NULL);
	path = ft_split(value, ':');
	if (!path)
		return (NULL);
	return (path);
}

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
	// builtin[6].key = "exit";
	// builtin[6].f = ft_exit;
}

static int	which_builtin(t_builtin *builtin, t_cmd *cmd)
{
	int	i;
	int	cmp;

	i = -1;
	while (++i < 6)
	{
		cmp = ft_strcmp(builtin[i].key, cmd->name);
		if (!cmp)
			return (i);
	}
	return (-1);
}

static int	ft_builtin(t_env *envp, t_cmd *cmd, t_builtin *builtin, int ret)
{
	if (builtin[ret].f(envp, cmd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	ft_router(t_env *envp, t_cmd *cmd)
{
	int			ret;
	char		**path;
	t_builtin	builtin[6];

	ft_init_builtin(builtin);
	ret = which_builtin(builtin, cmd);
	if (ret != -1)
		ft_builtin(envp, cmd, builtin, ret);
	else
	{
		path = path_value(envp, "PATH");
		if (!path)
			return ;
		ft_non_builtin(envp, cmd, path);
	}
	return ;
}
