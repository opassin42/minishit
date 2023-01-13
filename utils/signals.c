/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:39:55 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/13 15:53:05 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_handler(int sig)
{
	if (sig == SIGQUIT)
		ft_putstr_fd("\b\b \b\b", 2);
	else if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		g_data.status = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	parent_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: (core dumped)\n", 2);
		g_data.status = 131;
		g_data.sigquit = 1;
	}
	else if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		g_data.status = 130;
		g_data.sigint = 1;
		g_data.keeprunning = 1;
	}
}

void	sig_handler(int sig)
{
	if (g_data.pid)
		parent_handler(sig);
	else
		child_handler(sig);
}
