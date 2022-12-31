/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 02:41:11 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/31 13:38:01 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Init a tab with the shell env
** Then make a chained list with the env
*/

static t_env	*init_env(char **env, t_env *envp)
{
	int		i;
	void	*tmp;

	if (!env)
		return (NULL);
	envp->tab = env;
	envp->list = ft_lstnew((void *)env[0]);
	if (!envp->list)
		return (NULL);
	i = 0;
	while (env[++i])
	{
		tmp = (void *)env[i];
		ft_lstadd_back(&envp->list, ft_lstnew(tmp));
	}
	return (envp);
}

static t_var	*init_var(t_list **env_list)
{
	t_list	*tmp;
	t_var	*var;

	tmp = *env_list;
	var = ft_new_var(tmp);
	if (!var)
		return (NULL);
	tmp = tmp->next;
	while (tmp)
	{
		ft_var_addback(&var, ft_new_var(tmp));
		tmp = tmp->next;
	}
	return ((t_var *)var);
}

void	*init_shlvl(t_env *envp)
{
	t_var	*var;

	var = envp->var;
	while (var)
	{
		if (!ft_strcmp(var->name, "SHLVL"))
			return (var->value = "42");
		var = var->next;
	}
	return (NULL);
}

static char	**no_env(void)
{
	char	pwd[PATH_MAX];
	char	**a_env;

	a_env = (char **) NULL;
	if (getcwd(pwd, sizeof(pwd)) == NULL)
		return (NULL);
	a_env[0] = "SHLVL=42";
	if (!a_env[0])
		return (NULL);
	a_env[1] = ft_strjoin("PATH=", PATH_VALUE);
	if (!a_env[1])
		return (NULL);
	a_env[2] = ft_strjoin("PWD=", ft_strdup(pwd));
	if (!a_env[2])
		return (NULL);
	a_env[3] = 0;
	return (a_env);
}

t_env	*ft_getenv(char **env)
{
	t_env	*envp;

	if (!env)
		env = no_env();
	envp = (t_env *)push_top(&g_data.gc, sizeof(t_env));
	if (!envp)
		return (gc_free(), NULL);
	envp = init_env(env, envp);
	if (!envp)
		return (NULL);
	envp->var = init_var(&envp->list);
	if (!envp->var)
		return (NULL);
	return (envp);
}
