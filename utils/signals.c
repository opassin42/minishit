/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:39:55 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/17 20:34:51 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

<<<<<<< HEAD
void	intHandler(int sig) 
{
	keepRunning = 0;
	if (sig == SIGQUIT)
	{
		signal(SIGQUIT, SIG_IGN);
		ft_putstr_fd("\b\b  \b\b", 2);
		g_status = 131;
		// exit(0);
	}
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		g_status = 130;
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	// else if (sig == EOF)
	// 	exit(0);
	return ;
}

=======
void sig_handler(int sig) 
{
 if (sig == SIGINT)
    {
        keepRunning = 0;
        ft_putstr_fd("\n", 1);
        g_status = 130;
        rl_replace_line("", 1);
        rl_on_new_line();
        rl_redisplay();
    }
}
>>>>>>> opassin
