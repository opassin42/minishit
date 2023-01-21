/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 00:36:14 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/20 22:20:14 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	child_handler(int sig)
{
	if (sig == SIGQUIT){
		ft_putstr_fd("Quit: (core dumped)\n", 2);
	}
	else if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		g_data.status = 130;
		g_data.keeprunning = 1;
	}
}

void	parent_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		g_data.status = 131;
		g_data.keeprunning = 1;
		if (getpid() == getppid()) 
		{
			printf("Quit: (core dumped)\n");
			exit(printf("Quit: (core dumped)\n"));
		}
		else 
		{
			signal(SIGQUIT, SIG_IGN);
		}
	}
	else if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		g_data.status = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
