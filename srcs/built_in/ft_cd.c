/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:38:26 by ccouliba          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/05 00:37:21 by ccouliba         ###   ########.fr       */
=======
/*   Updated: 2022/07/12 01:48:56 by ccouliba         ###   ########.fr       */
>>>>>>> 32e3cefb54bf4eca551639a470025084468b8652
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

<<<<<<< HEAD
	tmp = (t_upvarenv *) malloc (sizeof (t_upvarenv));
	if (!tmp)
	{
=======
	tmp = push_top(&start, sizeof(t_upvarenv));
	if (!tmp)
	{
		gc_free();
>>>>>>> 32e3cefb54bf4eca551639a470025084468b8652
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
	if (!chdir(upvarenv->tmp))
	{
		if (upenv(envp, upvarenv) != 0)
			return (EXIT_FAILURE);
		free(upvarenv);
		return (EXIT_SUCCESS);
	}
	printf("minishell: cd: %s: %s\n", ++upvarenv->path, strerror(errno));
	free(upvarenv);
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
		ft_upenv(upvarenv, envp, "HOME", "PWD");
	else
	{
		upvarenv->path = ft_strdup(*cmd->param);
		if (ft_strlen(upvarenv->path) == 0)
			return (ft_no_home(upvarenv));
		else
		{
<<<<<<< HEAD
			if (!ft_strcmp(upvarenv->path, "-")
				|| !ft_strcmp(upvarenv->path, "--"))
=======
			if (!ft_strcmp(upvarenv->path, "-"))
>>>>>>> 32e3cefb54bf4eca551639a470025084468b8652
				ft_upenv(upvarenv, envp, "OLDPWD", "PWD");
			else if (upvarenv->path[0] == '/' || upvarenv->path[0] == '.'
				|| (upvarenv->path[0] == '.' && upvarenv->path[1] == '.'))
				ft_upenv(upvarenv, envp, upvarenv->path, "PWD");
			else if (is_alphanum(upvarenv))
				ft_upenv(upvarenv, envp, "PWD", "PWD");
		}
	}
	return ((int)ft_chdir(envp, upvarenv));
}
