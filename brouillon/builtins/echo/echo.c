/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:13:57 by dsaada            #+#    #+#             */
/*   Updated: 2022/07/30 12:48:54 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"
#include "../../global.h"

int	ft_echo(t_cmd *cmd, t_env *env)
{
	int	i;
	int	j;
	int	nflag;
	int	valid;

	(void)env;
	i = 0;
	j = 0;
	valid = 0;
	if (!cmd->params[1])
	{
		write(1, "\n", 1);
		g_status = EXIT_SUCCESS;
		return (SUCCESS);
	}
	while (cmd->params[++i] != NULL)
	{
		nflag = 0;
		j = 0;
		while (cmd->params[i][j] != '\0')
		{
			if (cmd->params[i][0] == '-' && !nflag)
			{
				if (cmd->params[i][1] == 'n')
				{
					nflag = 1;
					j += 2;
				}
				else
					break ;
			}
			if (nflag && cmd->params[i][j] == 'n')
			{
				valid = 1;
				j++;
			}
			else if (nflag && cmd->params[i][j] != 'n')
			{
				if (cmd->params[i][j] == '\0'
					|| (cmd->params[i][j] == '\\'
					&& cmd->params[i][j + 1] == 'n'))
				{
					valid = 1;
					break ;
				}
				else
				{
					nflag = 0;
					break ;
				}
			}
			else
				j++;
		}
		if (nflag == 0)
		{
			while (cmd->params[i])
			{
				write(1, cmd->params[i], ft_strlen(cmd->params[i]));
				i++;
				if (cmd->params[i])
					write(1, " ", 1);
			}
			if (valid != 1)
				write(1, "\n", 1);
			g_status = EXIT_SUCCESS;
			return (SUCCESS);
		}
	}
	g_status = EXIT_SUCCESS;
	return (SUCCESS);
}
