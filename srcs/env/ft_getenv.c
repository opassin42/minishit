/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 02:41:11 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/06 23:43:26 by ccouliba         ###   ########.fr       */
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

static void	init_shlvl(t_env *envp)
{
	t_var	*var;

	if (!envp)
		return ;
	var = envp->var;
	if (!var)
		return ;
	while (var)
	{
		if (!ft_strcmp(var->name, "SHLVL"))
		{
			var->value = "42";
			return ;
		}
		var = var->next;
	}
	return ;
}

t_env	*ft_getenv(char **env)
{
	t_env	*envp;

	if (!env)
		return (NULL);
	{
		// env = when_no_env();
		// printf("*env = [%s]\n", *env);
	}
	envp = (t_env *)push_top(&g_data.gc, sizeof(t_env));
	if (!envp)
		return (gc_free(), NULL);
	envp = init_env(env, envp);
	if (!envp)
		return (NULL);
	envp->var = init_var(&envp->list);
	if (!envp->var)
		return (NULL);
	return (init_shlvl(envp), envp);
}
