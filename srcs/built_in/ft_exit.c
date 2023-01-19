/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:42:05 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/19 21:31:10 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit(t_env *envp, t_cmd *cmd)
{
	(void)envp;
	(void)cmd;
	gc_free();
	return (exit(g_data.status), 0);
}
