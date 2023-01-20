/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 03:34:51 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/20 22:33:27 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data	init_global(void)
{
	t_data	g_data;

	g_data.cmdsize = 0;
	g_data.status = 0;
	g_data.rd_error = 0;
	g_data.prev = -1;
	g_data.pfd[0] = -1;
	g_data.pfd[1] = -1;
	g_data.prompt = NULL;
	g_data.pid = -1;
	g_data.gc = 0;
	g_data.keeprunning = 1;
	return (g_data);
}

void	init_builtin(t_builtin *builtin)
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
