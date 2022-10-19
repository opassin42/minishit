/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <dsaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:55:56 by dsaada            #+#    #+#             */
/*   Updated: 2022/07/30 12:58:30 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	free_env(t_env *env)
{
	t_var	*current;
	t_var	*next;

	if (!env)
		return (SUCCESS);
	current = env->start;
	while (current != NULL)
	{
		if (current->name)
			free(current->name);
		if (current->value)
			free(current->value);
		next = current->next;
		free(current);
		current = next;
	}
	return (SUCCESS);
}

void	unset_from_env(t_env *env, char *str)
{
	t_var	*var;
	t_var	*tmp;

	var = env->start;
	while (var != NULL)
	{
		if (ft_strcmp(str, var->name) == SUCCESS)
		{
			tmp = var->next;
			delete_var(env, var);
			var = tmp;
		}
		else
			var = var->next;
	}
}

int	delete_var(t_env *env, t_var *var)
{
	if (var == env->start)
		env->start = var->next;
	else
	{
		var->prev->next = var->next;
		if (var->next != NULL)
			var->next->prev = var->prev;
	}
	if (var->name)
		free(var->name);
	if (var->value)
		free(var->value);
	free(var);
	env->size--;
	return (SUCCESS);
}
