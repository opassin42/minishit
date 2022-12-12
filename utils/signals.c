/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:39:55 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/12 02:10:28 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Can't have the right return when interrupt a process by SIGINT
*/
void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_data.keeprunning = 1;
		ft_putstr_fd("\n", 1);
		g_data.status = 130;
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

// void	parent_signal(int sig)
// {
// 	if (sig == SIGQUIT)
// 		ft_putstr_fd("\b\b  \b\b", 2);
// 	if (sig == SIGINT)
// 	{
// 		ft_putstr_fd("\n", 1);
// 		rl_replace_line("", 1);
// 		rl_on_new_line();
// 		rl_redisplay();
// 		g_data.status = 130;
// 	}
// }

// void	child_signal(int sig)
// {
// 	if (sig == SIGQUIT)
// 	{
// 		ft_putstr_fd("Quit: (core dumped)\n", 2);
// 		g_data.status = 131;
// 		// g_ms.sigquit = 1;
// 	}
// 	else if (sig == SIGINT)
// 	{
// 		ft_putstr_fd("\n", 2);
// 		g_data.status = 130;
// 		// g_ms.sigint = 1;
// 	}
// }

// void	get_signal(int sig)
// {
// 	// if (g_ms.pid)
// 		child_signal(sig);
// 	// else
// 		parent_signal(sig);
// }
