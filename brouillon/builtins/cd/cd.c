/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <dsaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:57:08 by dsaada            #+#    #+#             */
/*   Updated: 2022/07/30 13:05:54 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"
#include "../pwd/pwd.h"
#include "../../global.h"	

static int	ft_strdlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_update_oldpwd(t_env *env)
{
	t_var	*var;
	char	*name;
	char	*oldpwd;

	name = ft_strdup("OLDPWD");
	if (!name)
		return (FAILURE);
	oldpwd = get_env_var(env, "PWD");
	if (!oldpwd)
	{
		free(name);
		return (FAILURE);
	}
	if (var_exist(env, name))
		unset_from_env(env, name);
	var = init_var(name, oldpwd);
	add_var(env, var);
	return (SUCCESS);
}

int	ft_update_pwd(t_env *env)
{
	t_var	*var;
	char	*name;
	char	*pwd;

	if (var_exist(env, "PWD"))
		unset_from_env(env, "PWD");
	name = ft_strdup("PWD");
	if (!name)
		return (FAILURE);
	pwd = get_cwd();
	if (!pwd)
	{
		free(name);
		return (FAILURE);
	}
	var = init_var(name, pwd);
	add_var(env, var);
	return (SUCCESS);
}

int	cd(char *path, t_env *env)
{
	char	*curpath;
	char	*tmp;
	char	*cd_path;

	cd_path = NULL;
	if (path)
		cd_path = ft_strdup(path);
	if (!cd_path)
	{
		cd_path = get_env_var(env, "HOME");
		if (ft_strlen(cd_path) == 0)
		{
			free(cd_path);
			write(2, "minishell: cd: HOME not set\n", 28);
			g_status = EXIT_FAILURE;
			return (SUCCESS);
		}
	}
	else if (!strcmp(cd_path, "-"))
		cd_path = get_env_var(env, "OLDPWD");
	else
	{
		if (cd_path[0] == '.')
		{
			if (cd_path[1] == '/')
			{
				curpath = get_cwd();
				cd_path = ft_strjoin(curpath, cd_path + 1);
			}			
		}
		else if (cd_path[0] == '~')
		{
			if (cd_path[1] == '/')
			{
				tmp = get_env_var(env, "HOME");
				if (!tmp)
					return (FAILURE);
				path = ft_strjoin(tmp, cd_path + 1);
				free(tmp);
			}
			else if (cd_path[1] == '\0')
				cd_path = get_env_var(env, "HOME");
			else
			{
				free(cd_path);
				perror(": error path syntax");
				g_status = EXIT_FAILURE;
				return (SUCCESS);
			}
		}
	}
	if (chdir(cd_path) == -1)
	{
		free(cd_path);
		write(2, "minishell: cd: ", 15);
		perror(path);
		g_status = EXIT_FAILURE;
		return (SUCCESS);
	}
	if (ft_update_oldpwd(env) == FAILURE)
		return (FAILURE);
	if (ft_update_pwd(env) == FAILURE)
		return (FAILURE);
	g_status = EXIT_SUCCESS;
	free(cd_path);
	return (SUCCESS);
}

int	ft_cd(t_cmd *cmd, t_env *env)
{
	if (ft_strdlen(cmd->params) > 2)
	{
		write(2, "minishell : cd: too many arguments\n", 35);
		g_status = EXIT_FAILURE;
		return (SUCCESS);
	}
	return (cd(cmd->params[1], env));
}
