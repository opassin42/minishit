/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 03:35:24 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/27 03:30:32 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data	init_global(void)
{
	t_data	g_data;

	g_data.status = 0;
	// g_data.sigint = 0;
	// g_data.sigquit = 0;
	g_data.pid = 0;
	g_data.gc = 0;
	g_data.keeprunning = 1;
	return (g_data);
}

void	init_sigflag(void)
{
	g_data.sigint = 0;
	g_data.sigquit = 0;
}
