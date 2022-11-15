/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 00:36:14 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/14 20:43:29 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** ctrl + d -> exit ingoing shell IF NO COMMAND = exit(0)
** ctrl + c -> SIGINT print new prompt on a new line (130).
** ctrl + \ -> SIGQUIT do nothing (131) if no ingoing op ; coredump(...) 
*/
// void	init_status(t_status g_stat)
// {
// 	g_stat.ret = 0;
// 	g_stat.sigint = 0;
// 	g_stat.sigquit = 0;
// }

// int	signal_handler(int sig)
// {
// 	if (sig == SIGINT)
// 		// new_prompt
// 	else if (sig == SIG)
// }
