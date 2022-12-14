/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:42:05 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/14 06:45:57 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_nb(char *s)
{
	while (*s)
	{
		if (s[0] == '-')
			s++;
		if (*s >= 48 && *s <= 57)
			s++;
		else
			return (0);
	}
	return (1);
}

int	ft_exit(t_env *envp, t_cmd *cmd)
{
	int		ret;

	(void)envp;
	ret = g_data.status;
	if (cmd && cmd->param && cmd->param[0])
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
		ret %= 256;
		ret = 256 - ret;
	}
	return (exit(ret), ret);
}
