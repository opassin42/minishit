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
