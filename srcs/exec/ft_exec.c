/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:48:13 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/20 23:54:25 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	set_builtin_id(t_cmd *cmd, t_builtin *builtin)
{
	init_builtin(builtin);
	cmd->id = which_builtin(builtin, cmd);
	return ;
}

int	ft_process(t_env *envp, t_cmd *cmd)
{
	t_builtin	builtin[7];

	set_builtin_id(cmd, builtin);
	if (cmd->id == -1 || g_data.cmdsize > 1)
	{
		if (pipe(g_data.pfd) < 0)
			return (perror("minishell: pipe:"), errno);
		cmd->pid = fork();
		if (cmd->pid < 0)
			return (perror("minishell: fork:"), errno);
		if (cmd->pid == 0)
		{
			router(envp, cmd, builtin);
			ft_exit(envp, cmd);
		}
		else
			p_father(cmd);
	}
	else if (g_data.cmdsize == 1)
		exec_builtin(envp, cmd, builtin);
	return (g_data.status);
}

int	ft_exec(t_env *envp, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	g_data.cmdsize = ft_cmdsize(cmd);
	while (cmd)
	{
		if (cmd->ret == -1)
			return (EXIT_FAILURE);
		g_data.status = ft_process(envp, cmd);
		cmd = cmd->next;
	}
	return (ft_waitpid(tmp), g_data.status);
}
