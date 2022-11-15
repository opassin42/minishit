/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:15:53 by dsaada            #+#    #+#             */
/*   Updated: 2022/07/30 15:51:48 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"
#include "../../global.h"

int	ft_exit_program(t_cmd_list *cmd_list, t_env *env)
{
	free_cmd_list(cmd_list);
	free_env(env);
	rl_clear_history();
	exit(g_status);
	return (FAILURE);
}

int	ft_exit(t_cmd_list *cmd_list, t_cmd *cmd, t_env *env)
{
	int	i;
	int	status;
	int	errflag;

	i = 0;
	errflag = 0;
	while (cmd->params[i] != NULL)
		i++;
	//write(1, "exit\n", 5);
	if (i > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		g_status = 1;
		ft_exit_program(cmd_list, env);
		return (SUCCESS);
	}
	if (cmd->params[1] == NULL)
	{
		g_status = 0;
		ft_exit_program(cmd_list, env);
		return (SUCCESS);
	}
	status = ft_atoi_mod256(cmd->params[1], &errflag);
	if (errflag == FAILURE)
	{
		g_status = 255;
		write(2, "minishell: exit: ", 17);
		write(2, cmd->params[1], ft_strlen(cmd->params[1]));
		write(2, ": numeric argument required\n", 28);
		ft_exit_program(cmd_list, env);
	}
	else
	{
		g_status = status;
		ft_exit_program(cmd_list, env);
	}
	return (SUCCESS);
}
