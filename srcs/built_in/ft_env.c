/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:41:35 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/14 21:46:35 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_print_env(t_var *var)
{
	while (var)
	{
		printf("%s\e[0;33m=\e[0m%s\n", var->name, var->value);
		var = var->next;
	}
}

void	ft_export_env(t_var *var)
{
	t_var	*var_env;

	var_env = NULL;
	if (var)
	{
		var_env = var;
		var_env = var_index(&var_env);
	}
	while (var_env)
	{
		printf("declare -x %s\e[0;33m=\e[0m%s\n", var_env->name, var_env->value);
		var_env = var_env->next;
	}
}

int	ft_env(t_env *envp, t_cmd *cmd)
{
	char	**tmp;
	t_var	*var;

	if (!envp)
		return (EXIT_FAILURE);
	var = envp->var;
	if (!var)
		return (EXIT_FAILURE);
	if (cmd->param && *cmd->param)
	{
		tmp = cmd->param;
		syntax_error(*tmp, ERRNO_3, 2, ft_putstr_fd);
		return (127);
	}
	return (ft_print_env(var), EXIT_SUCCESS);
}
