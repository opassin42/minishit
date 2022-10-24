/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opassin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 13:31:35 by opassin           #+#    #+#             */
/*   Updated: 2022/10/25 00:04:58 by opassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "../../minishell.h"


char	*getenv_val(t_env *envp, char *name)
{
	t_var	*var;

	var = envp->var;
	while (var)
	{
		if (!ft_strcmp(var->name, var_name))
			return (var->value);
		var = var->next;
	}
	return (NULL);
}

/*
 * ft_cd 		: Change Directory 
 * Type 		: integer
 * Parametre	: aucun
 * Valeur de retour: 0 en cas de succes;
 */
 
 int ft_cd(t_env *envp, char *path)
{
	char *cdpath;

	if (!path)
	{
		cdpath = getenv_val(envp, "HOME");
		if (ft_strlen(cdpath) == 0 )
		{
			printf("minishell: cd: HOME not set\n");
			return (1);
		}
		else if (path)

	}
	

}
