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
	char *path;
}	t_upvarenv;

static int		upenv(t_env *envp,  t_upvarenv *upvarenv)
{
	upvarenv->pwd = get_pwd();
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
	tmp->path = NULL;
	return (tmp);
}

void	ft_upenv(t_upvarenv *upvarenv, t_env *envp, char *s1, char *s2)
{
	if (upvarenv->path != NULL && !ft_strcmp(s1, upvarenv->path))
		upvarenv->tmp = upvarenv->path;
	else if (upvarenv->path[0] == 126 && upvarenv->path[1])
		upvarenv->tmp = ft_strdup(ft_strjoin(get_in_env(envp, "HOME"), upvarenv->path));
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

int 	is_alphanum(t_upvarenv *upvarenv)
{

	if ((upvarenv->path[0] >= 65 && upvarenv->path[0] <= 90)
		|| (upvarenv->path[0] >= 97 && upvarenv->path[0] <= 122)
		|| (upvarenv->path[0] == 126 && upvarenv->path[1] == 47))
		return (1);
	return (0);
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

	upvarenv = init_upvarenv();
	printf("%s kkkkkkkkk", *cmd->param);
	if (!cmd->param || !ft_strcmp(*cmd->param, "~"))
		ft_upenv(upvarenv, envp, "HOME", "PWD");
	else
	{
		upvarenv->path = ft_strdup(*cmd->param);
		if (ft_strlen(upvarenv->path) == 0)
			return (ft_no_home(upvarenv));
		else
		{
			if(!ft_strcmp(upvarenv->path, "-"))
				ft_upenv(upvarenv, envp, "OLDPWD", "PWD");
			else if (upvarenv->path[0] == '/' || upvarenv->path[0] == '.' || (upvarenv->path[0] == '.' && upvarenv->path[1] == '.'))
				ft_upenv(upvarenv, envp, upvarenv->path, "PWD");
			else if(is_alphanum(upvarenv))
			{
					ft_upenv(upvarenv, envp, "HOME", "PWD");
				//upvarenv->tmp = ft_strjoin(get_in_env(envp, "PWD"), upvarenv->path);
				//upvarenv->oldpwd = ft_strdup(get_in_env(envp, "PWD"));
			}
		}
	}
	return((int)ft_chdir(envp, upvarenv));
}

	


