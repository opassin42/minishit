/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:56:53 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/13 20:22:24 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * init_upvarenv : (utils) update oldpwd and pwd 
 * Type 		 : static int
 * Parameter	 : integer
 * Return value  : 0 in success
 */
static int	upenv(t_env *envp, t_upvarenv *upvarenv)
{
	upvarenv->pwd = get_pwd();
	up_in_env(envp, "OLDPWD", upvarenv->oldpwd);
	up_in_env(envp, "PWD", upvarenv->pwd);
	return (EXIT_SUCCESS);
}

/*
 * init_upvarenv : init the struct upvarenv
 * Type 		 : static struct (t_upvarenv)
 * Parameter	 : void
 * Return value  : tmp (struct upvarenv)
 */
static t_upvarenv	*init_upvarenv(void)
{
	t_upvarenv	*tmp;

	tmp = push_top(&g_data.gc, sizeof(t_upvarenv));
	if (!tmp)
	{
		gc_free();
		printf("minishell: cd: allocate error\n");
		return (NULL);
	}
	tmp->oldpwd = NULL;
	tmp->pwd = NULL;
	tmp->tmp = NULL;
	tmp->path = NULL;
	return (tmp);
}

/*
 * ft_upenv 	: update la valeur des variable d'environnement OLDPWD et PWD
 * Type 		: void
 * Parametre	: struct upvarenv, list env, chaines de characteres s1 et s2
 * Return value : aucune
 */
static void	ft_upenv(t_upvarenv *upvarenv, t_env *envp, char *s1, char *s2)
{
	if (upvarenv->path == NULL)
		upvarenv->tmp = ft_strdup(get_in_env(envp, "HOME"));
	else if (upvarenv->path != NULL && !ft_strcmp(s1, upvarenv->path))
		upvarenv->tmp = upvarenv->path;
	else if (upvarenv->path[0] == '~' && upvarenv->path[1])
		upvarenv->tmp = ft_strdup(ft_strjoin(get_in_env(envp, "HOME"),
					++(upvarenv->path)));
	else if (is_alphanum(upvarenv))
	{
		upvarenv->path = ft_strjoin("/", upvarenv->path);
		upvarenv->tmp = ft_strdup(ft_strjoin(get_in_env(envp, "PWD"),
					upvarenv->path));
	}
	else
		upvarenv->tmp = ft_strdup(get_in_env(envp, s1));
	upvarenv->oldpwd = ft_strdup(get_in_env(envp, s2));
	upvarenv->pwd = upvarenv->tmp;
}

/*
 * ft_chdir 	: Change Directory utils
 * Type 		: integer
 * Parameter	: list env, struct upvarenv
 * Return value : 0 in case of success or 1 in case of fail
 */
static int	ft_chdir(t_env *envp, t_upvarenv *upvarenv)
{
	if (upvarenv->tmp)
	{
		if (!chdir(upvarenv->tmp))
		{
			if (upenv(envp, upvarenv) != 0)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
	}
	printf("minishell: cd: %s: %s\n", ++upvarenv->path, strerror(errno));
	return (EXIT_FAILURE);
}

/*
 * ft_cd 		: Change Directory 
 * Type 		: integer
 * Parametre	: aucun
 * Return value : 0 en cas de succes;
 */
int	ft_cd(t_env *envp, t_cmd *cmd)
{
	t_upvarenv	*upvarenv;

	upvarenv = init_upvarenv();
	if (!cmd->param || !ft_strcmp(*cmd->param, "~"))
	{
		if (get_in_env(envp, "HOME") == NULL)
			return (ft_no_home(upvarenv));
		ft_upenv(upvarenv, envp, "HOME", "PWD");
	}
	else
	{
		upvarenv->path = ft_strdup(*cmd->param);
		if (ft_strlen(upvarenv->path) == 0)
			return (ft_no_home(upvarenv));
		else
			update_env(envp, upvarenv, ft_upenv);
	}
	return ((int)ft_chdir(envp, upvarenv));
}
