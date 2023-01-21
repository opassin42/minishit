/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:42:05 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/21 13:57:23 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_nb(char *s)
{
	int	i;

	i = -1;
	if (s[0] == '-')
		i++;
	while (s[++i])
		if (s[i] < 48 || s[i] > 57)
			return (0);
	return (1);
}

int	ft_exit(t_env *envp, t_cmd *cmd)
{
	(void)envp;
	if (cmd && cmd->param)
	{
		if (cmd->param[1] || !is_nb(cmd->param[0]))
		{
			if (is_nb(cmd->param[0]) == 0)
				return (printf("exit\n"), g_data.status = 2,
					exec_error(cmd->name, ERRNO_8, 2, ft_putstr_fd), 2);
			else
			{
				printf("exit\nminishell: %s: %s\n", cmd->name, ERRNO_7);
				return (g_data.status = 1);
			}
		}
		else
			g_data.status = ft_atoi(cmd->param[0]);
	}
	if (g_data.status < 0)
	{
		g_data.status *= (-1);
		g_data.status %= 256;
		g_data.status = 256 - g_data.status;
	}
	return (gc_free(), exit(g_data.status), g_data.status);
}
