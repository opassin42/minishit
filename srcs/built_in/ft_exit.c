/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:42:05 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/11 23:01:45 by ccouliba         ###   ########.fr       */
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
				cmd_error(cmd->name, ERRNO_4, 2, ft_putstr_fd);
			else
				cmd_error(cmd->name, ERRNO_5, 2, ft_putstr_fd);
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
