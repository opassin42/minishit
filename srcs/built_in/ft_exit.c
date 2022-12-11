/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:42:05 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/15 17:39:50 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		ft_exit(t_env *envp, t_cmd *cmd)
{
	(void)envp;
	long		ret;

	ret = g_status;
	if (*(cmd->param))
	{
		ret = ft_atoi(cmd->param[0]);
		if (cmd->param[1])
			return(ft_putstr_fd("minishell: exit: too many arguments\n", 1), g_status);
		else if (is_nb(cmd->param[0]))
			return(ft_putstr_fd("minishell: exit: numeric argument required\n", 1), g_status);
	}
	gc_free();
	if (ret < 0)
	{
		ret *= (-1);
		ret %= 256;
		ret = 256 - ret;

		exit ();
	}
}
