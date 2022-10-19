/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:19:23 by dsaada            #+#    #+#             */
/*   Updated: 2022/07/26 14:59:37 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"
#include "../../global.h"

int	ft_unset(t_cmd *cmd, t_env *env)
{
	int	i;

	i = 0;
	while (cmd->params[i] != NULL)
	{
		if (check_valid_identifier(cmd->params[i]) == SUCCESS)
		{
			unset_from_env(env, cmd->params[i]);
			g_status = EXIT_SUCCESS;
		}
		else
		{
			g_status = EXIT_FAILURE;
			write(2, "minishell: unset: `", 19);
			write(2, cmd->params[i], ft_strlen(cmd->params[i]));
			write(2, "': not a valid identifier\n", 26);
		}
		i++;
	}
	return (SUCCESS);
}
