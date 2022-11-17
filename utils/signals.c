/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:39:55 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/17 07:27:35 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	intHandler(int sig) 
{
	keepRunning = 0;
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("\nQuit (core dumped)\n", 2);
		g_status = 131;
		exit(0);
	}
	else if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		g_status = 130;
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == EOF)
		exit(0);
	return ;
}

