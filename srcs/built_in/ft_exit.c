/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:42:05 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/11 03:07:54 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit(t_env *envp, t_cmd *cmd)
{
	int		ret;

	(void)envp;
	ret = 0;
	if (cmd->param && *(cmd->param))
	{
		ret = ft_atoi(cmd->param[0]);
		if (cmd->param[1] || !is_nb(cmd->param[0]))
		{
			if (!is_nb(cmd->param[0]))
				ft_putstr_fd("exit\n minishell: exit: numeric argument required\n", 1);
			else
				ft_putstr_fd("exit\n minishell: exit: too many arguments\n", 1);
			ret = 2;
		}
	}
	gc_free();
	if (ret < 0)
	{
		ret *= (-1);
		exit (256 - (ret % 256));
	}
	exit (ret % 256);
	return (0);
}
