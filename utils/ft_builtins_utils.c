/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:38:26 by opassin           #+#    #+#             */
/*   Updated: 2023/01/12 18:59:41 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * ft_no_home 	: print the home's path error 
 * Type 		: integer
 * Parameter	: struct upvarenv
 * Return value: 1 in case of fail
 */
int	ft_no_home(t_upvarenv *upvarenv)
{
	(void)upvarenv;
	printf("minishell: cd: HOME not set\n");
	return (1);
}

/*
 * is_alphanum 	: check if the character is alphanum
 * Type 		: integer
 * Parameter	: struct upvarenv
 * Return value: 1 in case of success or 0 in case of fail
 */
int	is_alphanum(t_upvarenv *upvarenv)
{
	if ((upvarenv->path[0] >= 48 && upvarenv->path[0] <= 57)
		|| (upvarenv->path[0] >= 65 && upvarenv->path[0] <= 90)
		|| (upvarenv->path[0] >= 97 && upvarenv->path[0] <= 122)
		|| (upvarenv->path[0] == 126 && upvarenv->path[1] == 47))
		return (1);
	return (0);
}

void	update_env(t_env *envp, t_upvarenv *upvarenv, void (*f)())
{
	if (!ft_strcmp(upvarenv->path, "-")
		|| !ft_strcmp(upvarenv->path, "--"))
		f(upvarenv, envp, "OLDPWD", "PWD");
	else if (upvarenv->path[0] == '/' || upvarenv->path[0] == '.'
		|| (upvarenv->path[0] == '.' && upvarenv->path[1] == '.'))
		f(upvarenv, envp, upvarenv->path, "PWD");
	else if (is_alphanum(upvarenv))
		f(upvarenv, envp, "PWD", "PWD");
}

int	replace_if_exists(t_env *envp, t_var *new_var)
{
	t_var	*var;

	var = envp->var;
	while (var)
	{
		if (!ft_strcmp(var->name, new_var->name))
		{
			var->value = new_var->value;
			return (EXIT_FAILURE);
		}
		var = var->next;
	}
	return (EXIT_SUCCESS);
}
