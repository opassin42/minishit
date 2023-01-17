/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_in_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 23:14:14 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/17 18:31:38 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_in_env(t_env *envp, char *name)
{
	t_var	*var;

	if (!name || !envp)
		return (NULL);
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

	if (!s || !var_name || !envp)
		return ;
	var = envp->var;
	while (var)
	{
		if (!ft_strcmp(var->name, var_name))
			(var->value) = s;
		var = var->next;
	}
	return ;
}
