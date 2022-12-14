/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:39:55 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/15 00:29:30 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	restore_prompt(int sig)
{
	(void)sig;
	g_data.status = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// void	ctrl_c(int sig)
// {
// 	(void)sig;
// 	g_data.status = 130;
// 	ft_putstr_fd("\n", 2);
// }

// void	back_slash(int sig)
// {
// 	(void)sig;
// 	g_data.status = 131;
// 	ft_putstr_fd("Quit: (core dump)\n", 2);
// }

// void	sig_handler(int sig)
// {
// 	if (sig == 1)
// 	{
// 		signal(SIGINT, restore_prompt);
// 		signal(SIGQUIT, SIG_IGN);
// 	}
// 	if (sig == 2)
// 	{
// 		signal(SIGINT, ctrl_c);
// 		signal(SIGQUIT, back_slash);
// 	}
// 	if (sig == 3)
// 	{
// 		printf("exit\n");
// 		exit(g_data.status);
// 	}
// }

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
		printf("99\n");
	}
	return ;
}

static void	child_signal(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("100Quit: (core dump)\n", 2);
		g_data.status = 131;
		// g_data.keeprunning = 1;
		return ;
	}
	else if (sig == SIGINT)
	{
		ft_putstr_fd("10\n", 2);
		g_data.keeprunning = 1;
		g_data.status = 130;
	}
	if (g_data.pid != 0)
	{
		printf("parent\n");
		restore_prompt(sig);
		g_data.status = 130;
		g_data.keeprunning = 1;
		//here i have to find a way to stop right up there
	}
}

void	sig_handler(int sig)
{
	if (g_data.pid)
		child_signal(sig);
	else
		parent_signal(sig);
}
