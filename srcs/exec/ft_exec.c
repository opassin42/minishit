/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:48:13 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/21 13:26:30 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	set_builtin_id(t_cmd *cmd, t_builtin *builtin)
{
	init_builtin(builtin);
	cmd->id = which_builtin(builtin, cmd);
	return ;
}

static int	ft_process(t_env *envp, t_cmd *cmd)
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
	int		status;
	t_cmd	*tmp;

	tmp = cmd;
	g_data.cmdsize = ft_cmdsize(cmd);
	while (cmd)
	{
		status = ft_process(envp, cmd);
		cmd = cmd->next;
	}
	if (g_data.pfd[0] != -1)
		close(g_data.pfd[0]);
	if (g_data.pfd[1] != -1)
		close(g_data.pfd[1]);
	if (g_data.prev != -1)
		close (g_data.prev);
	return (ft_waitpid(tmp), status | g_data.status);
}
