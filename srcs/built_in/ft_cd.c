/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:38:26 by ccouliba          #+#    #+#             */
/*   Updated: 2022/07/12 01:48:56 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

typedef struct s_upvarenv
{
	char *oldpwd;
	char *pwd;
	char *tmp;
}	t_upvarenv;

static char	*getenv_val(t_env *envp, char *name)
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

static int		upenv(t_env *envp,  t_upvarenv *upvarenv)
{
	t_var	*var;

	var = envp->var;
	if (var)
	{	
		while (var)
		{
			if (!ft_strcmp(var->name, "OLDPWD"))
				(var->value) = upvarenv->oldpwd;
			else if (!ft_strcmp(var->name, "PWD"))
				(var->value) = upvarenv->pwd;
			var = var->next;
		}
	}
	return (0);
}

static void	init_upvarenv(t_upvarenv **upvarenv)
{
	t_upvarenv *tmp;

	tmp = *upvarenv;
	tmp->oldpwd = NULL;
	tmp->pwd = NULL;
	tmp->tmp = NULL;
}

/*
 * ft_cd 		: Change Directory 
 * Type 		: integer
 * Parametre	: aucun
 * Valeur de retour: 0 en cas de succes;
 */
 
 int ft_cd(t_env *envp, t_cmd *cmd)
{
	t_upvarenv *upvarenv;
	char *path;

	
	upvarenv = (t_upvarenv*)malloc(sizeof(t_upvarenv));	
	init_upvarenv(&upvarenv);

	if (!cmd->param || !ft_strcmp(*cmd->param, "~"))
	{
		
		upvarenv->tmp = ft_strdup(getenv_val(envp, "HOME"));
		upvarenv->oldpwd = ft_strdup(getenv_val(envp, "PWD"));
		upvarenv->pwd = upvarenv->tmp;
	}
	else
	{
		path = ft_strdup(*cmd->param);
		if (ft_strlen(path) == 0)
		{
			free(upvarenv);
			printf("minishell: cd: HOME not set\n");
			return (1);
		}
		else
		{
			if(!ft_strcmp(path, "-"))
			{
				upvarenv->tmp = ft_strdup(getenv_val(envp, "OLDPWD"));
				upvarenv->oldpwd = ft_strdup(getenv_val(envp, "PWD"));
				upvarenv->pwd = upvarenv->tmp;
			}
			else if (path[0] == '/' || path[0] == '.' || (path[0] == '.' && path[1] == '.'))
			{
				upvarenv->tmp = path;
				upvarenv->oldpwd = ft_strdup(getenv_val(envp, "PWD"));
				upvarenv->pwd = upvarenv->tmp;
			}
			else
			{
				upvarenv->tmp = ft_strjoin(upvarenv->pwd, path);
				upvarenv->oldpwd = ft_strdup(getenv_val(envp, "PWD"));
				upvarenv->pwd = upvarenv->tmp;
			}
		}
	}
	if(!chdir(upvarenv->tmp))
	{
		if(!upenv(envp, upvarenv))
			return (1);
		free(upvarenv);
		return (0);
	}
	free(upvarenv);
	return (1);
}
	


