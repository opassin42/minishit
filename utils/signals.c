/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:39:55 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/14 13:35:12 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_signal(void)
{
	g_data.sigint = 0;
	g_data.sigquit = 0;
}

static void	parent_signal(int sig)
{
	if (sig == SIGQUIT)
	{
		g_data.keeprunning = 1;
		g_data.status = 131;
		ft_putstr_fd("\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		printf("HERE\n");
	return ;
}

static void	child_signal(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("\n", 2);
		g_data.status = 131;
		g_data.sigint = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		g_data.status = 130;
		ft_putstr_fd("\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		if (g_data.pid != 0)
			return ;
	}
	if (g_data.pid == 0)
	{
		g_data.status = 130;
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

void	sig_handler(int sig)
{
	if (g_data.pid)
		child_signal(sig);
	else
		parent_signal(sig);
}
