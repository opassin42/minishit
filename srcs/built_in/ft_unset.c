/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:42:36 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/05 04:42:38 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_var(t_var *var)
{
	free(var->name);
	free(var->value);
	var = NULL;
}

int	ft_unset(t_env *envp, t_cmd *cmd)
{
	t_var	*var;
	t_var	*var_next;
	t_var	*tmp;
	char	*var_name;

	var = envp->var;
	var_name = *cmd->param;
	if (!ft_strcmp(var->name, var_name))
	{
		envp->var = var->next;
		ft_free(var);
	}
	else
	{
		var_next = var->next;
		while (var)
		{
			if (var_next && !ft_strcmp(var_next->name, var_name))
			{
				tmp = var_next->next;
				ft_free(var_next);
				var->next = tmp;
				return (EXIT_SUCCESS);
			}
			var = var->next;
			var_next = var->next;
		}
	}
	return (EXIT_FAILURE);
}