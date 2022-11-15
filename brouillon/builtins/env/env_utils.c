/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <dsaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:30:54 by dsaada            #+#    #+#             */
/*   Updated: 2022/07/30 12:57:14 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_var	*init_var(char	*name, char	*value)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	var->name = name;
	var->value = value;
	var->print = 0;
	var->prev = NULL;
	var->next = NULL;
	return (var);
}

void	init_env(t_env *env)
{
	env->size = 0;
	env->start = NULL;
	env->end = NULL;
}

void	add_var(t_env *env, t_var *var)
{
	t_var	*current;

	if (env->start)
	{
		current = env->start;
		while (current->next != NULL)
			current = current->next;
		var->prev = current;
		current->next = var;
		env->end = var;
	}
	else
	{
		env->start = var;
		env->end = var;
	}
	env->size++;
}

void	print_env(t_env *env)
{
	t_var	*current;

	current = env->start;
	while (current != NULL)
	{
		if (current->value != NULL)
			printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}

int	var_exist(t_env *env, char *str)
{
	t_var	*var;

	var = env->start;
	while (var != NULL)
	{
		if (ft_strcmp(str, var->name) == SUCCESS)
		{
			return (SUCCESS);
		}
		else
			var = var->next;
	}
	return (FAILURE);
}
