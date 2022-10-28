/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_in_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 23:14:14 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/25 09:01:21 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	init_shlvl(t_env *envp)
// {
// 	t_var	*var;

// 	var = envp->var;
// 	while (var)
// 	{
// 		if (!ft_strcmp(var->name, "SHLVL"))
// 			var->value = upgrade_shlvl((var->value));
// 		var = var->next;
// 	}
// }

void	find_in_env(t_env *envp, char *var_name, char *(*f)())
{
	t_var	*var;

	var = envp->var;
	while (var)
	{
		if (!ft_strcmp(var->name, var_name))
			(var->value) = f((var->value));
		var = var->next;
	}
	return ;
}

char	*get_in_env(t_env *envp, char *name)
{
	t_var	*var;

	var = envp->var;
	if (var)
	{	
		while (var)
		{
			if (!ft_strcmp(var->name, name))
				return (var->value);
			var = var->next;
		}
	}
	return (NULL);
}

void	up_in_env(t_env *envp, char *var_name, char *s)
{
	t_var	*var;

	var = envp->var;
	while (var)
	{
		if (!ft_strcmp(var->name, var_name))
			(var->value) = s;
		var = var->next;
	}
	return ;
}
