/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 00:36:14 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/19 22:37:45 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	child_handler(int sig)
{
	if (sig == SIGQUIT)
		ft_putstr_fd("\b\b \b\b", 2);
	else if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		g_data.status = 130;
		g_data.sigint = 1;
		g_data.keeprunning = 1;
	}
}

void	parent_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: (core dumped)\n", 2);
		g_data.status = 131;
		g_data.keeprunning = 1;
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
