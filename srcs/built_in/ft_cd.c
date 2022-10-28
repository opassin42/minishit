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

static int		upenv(t_env *envp,  t_upvarenv *upvarenv)
{
	up_in_env(envp, "OLDPWD", upvarenv->oldpwd);
	up_in_env(envp, "PWD", upvarenv->pwd);
	return (0);
}

static t_upvarenv	*init_upvarenv(void)
{
	t_upvarenv *tmp;


	tmp = (t_upvarenv*)malloc(sizeof(t_upvarenv));
	if(!tmp)
	{
		printf("minishell: cd: allocate error\n");
		return (NULL);
	}
	tmp->oldpwd = NULL;
	tmp->pwd = NULL;
	tmp->tmp = NULL;
	return (tmp);
}

void	ft_upenv(t_upvarenv *upvarenv, t_env *envp, char *s1, char *s2, char *path)
{
	if (path && !ft_strcmp(s1, path))
		upvarenv->tmp = path;
	else
		upvarenv->tmp = ft_strdup(get_in_env(envp, s1));
	upvarenv->oldpwd = ft_strdup(get_in_env(envp, s2));
	upvarenv->pwd = upvarenv->tmp;
}

int		ft_chdir(t_env *envp, t_upvarenv *upvarenv)
{
	if(!chdir(upvarenv->tmp))
	{
		if(upenv(envp, upvarenv) != 0)
			return (1);
		//up_in_env(envp, "PWD", pwd);
		free(upvarenv);
		return (0);
	}
	free(upvarenv);
	return (1);
}


int		ft_no_home(t_upvarenv *upvarenv)
{
	free(upvarenv);
	printf("minishell: cd: HOME not set\n");
	return (1);
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

	upvarenv = init_upvarenv();
	path = NULL;
	if (!cmd->param || !ft_strcmp(*cmd->param, "~"))
		ft_upenv(upvarenv, envp, "HOME", "PWD", path);
	else
	{
		path = ft_strdup(*cmd->param);
		if (ft_strlen(path) == 0)
			return (ft_no_home(upvarenv));
		else
		{
			if(!ft_strcmp(path, "-"))
				ft_upenv(upvarenv, envp, "OLDPWD", "PWD", path);
			else if (path[0] == '/' || path[0] == '.' || (path[0] == '.' && path[1] == '.'))
				ft_upenv(upvarenv, envp, path, "PWD", path);
			else
			{
				upvarenv->tmp = ft_strjoin(get_in_env(envp, "PWD"), path);
				upvarenv->oldpwd = ft_strdup(get_in_env(envp, "PWD"));
				upvarenv->pwd = upvarenv->tmp;
			}
		}
	}
	return((int)ft_chdir(envp, upvarenv));
}

	


