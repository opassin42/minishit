/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:39:55 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/14 08:49:21 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_signal(void)
{
	g_data.sigint = 0;
	g_data.sigquit = 0;
}

// static void	parent_signal(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		g_data.keeprunning = 1;
// 		ft_putstr_fd("\n", 1);
// 		rl_replace_line("", 1);
// 		rl_on_new_line();
// 		rl_redisplay();
// 		g_data.status = 130;
// 	}
// 	if (sig == SIGQUIT)
// 		ft_putstr_fd("\b\b  \b\b", 1);
// 	return ;
// }

// static void	child_signal(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		ft_putstr_fd("\n", 1);
// 		g_data.status = 130;
// 		g_data.sigint = 1;
// 	}
// 	else if (sig == SIGQUIT)
// 	{
// 		ft_putstr_fd("Quit: (core dumped)\n", 1);
// 		g_data.status = 131;
// 		g_data.sigquit = 1;
// 	}
// }

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_data.keeprunning = 1;
		g_data.status = 130;
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	// if (g_data.pid)
	// 	child_signal(sig);
	// else
	// 	parent_signal(sig);
}
