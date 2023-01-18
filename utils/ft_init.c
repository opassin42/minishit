/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 03:35:24 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/13 19:40:27 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data	init_global(void)
{
	t_data	g_data;

	g_data.status = 0;
	g_data.pid = -1;
	g_data.gc = 0;
	g_data.keeprunning = 1;
	g_data.rd_error = 0;
	g_data.prompt = NULL;
	return (g_data);
}

void	init_sigflag(void)
{
	g_data.sigint = 0;
	g_data.sigquit = 0;
}
