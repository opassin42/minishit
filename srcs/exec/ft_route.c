/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_route.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:49:33 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/25 00:23:36 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static void	ft_init_builtin(t_builtin builtin)
// {
// 	builtin[0] = ft_echo;
// 	builtin[1] = ft_env;
// }

// void	ft_route(t_list **token, t_env envp, void (*f)())
// {
// 	// char	*s;
// 	// char	**tab;
// 	t_list	*tmp;

// 	tmp = *token;
// 	if (!ft_strcmp(tmp->val, "env"))
// 		ft_env(&envp, tmp);
// }

int	ft_route(t_env *envp, t_cmd *cmd)
{
	while (cmd)
	{
		if (!ft_strcmp(cmd->name, "echo"))
			ft_echo(envp, cmd);
		if (!ft_strcmp(cmd->name, "env"))
			ft_env(envp, cmd);
		if (!ft_strcmp(cmd->name, "pwd"))
			ft_pwd(envp, cmd);
		cmd = cmd->next;
	}
	// else if (!ft_strcmp(cmd, "exit"))
	// 	ft_exit(envp, cmd);
	// else if (!ft_strcmp(cmd, "export"))
	// 	ft_export(envp, cmd);
	// else if (!ft_strcmp(cmd, "cd"))
	// 	ft_cd(envp, cmd);
	// else if (!ft_strcmp(cmd, "pwd"))
	// 	ft_pwd(envp, cmd);
	// else if (!ft_strcmp(cmd, "unset"))
	// 	ft_unset(envp, cmd);
}
