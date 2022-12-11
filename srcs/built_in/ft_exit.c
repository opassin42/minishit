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

int	is_nb(char *s)
{
	while (*s)
	{
		if (!ft_is_digit(*s))
			return (EXIT_FAILURE);
		++s;
	}
	return (EXIT_SUCCESS);
}

int	ft_exit(t_env *envp, t_cmd *cmd)
{
	long	ret;

	(void)envp;
	ret = g_status;
	if (*(cmd->param))
	{
		ret = ft_atoi(cmd->param[0]);
		if (cmd->param[1])
			cmd_error(cmd->name, ERRNO_4, 2, ft_putstr_fd);
		else if (is_nb(cmd->param[0]))
			cmd_error(cmd->name, ERRNO_5, 2, ft_putstr_fd);
	}
	gc_free();
	if (ret < 0)
	{
		ret *= (-1);
		ret %= 256;
		ret = 256 - ret;
		exit (ret);
	}
	return (EXIT_SUCCESS);
}
