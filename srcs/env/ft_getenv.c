/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 02:41:11 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/17 23:39:37 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Init a tab with the shell env
** Then make a chained list with the env
*/

t_env	ft_init_env(char **env)
{
	int		i;
	void	*tmp;
	t_env	envp;

	envp.shlvl = 0;
	envp.tab = env;
	envp.list = ft_lstnew((void *)env[0]);
	i = 0;
	while (env[++i])
	{
		tmp = (void *)env[i];
		ft_lstadd_back(&envp.list, ft_lstnew(tmp));
	}
	return (envp);
}

t_var	*ft_init_var(t_list **env_list)
{
	t_list	*tmp;
	t_var	*var;

	tmp = *env_list;
	var = ft_new_var(tmp);
	if (!var)
		return (gc_free(), NULL);
	tmp = tmp->next;
	while (tmp)
	{
		ft_var_addback(&var, ft_new_var(tmp));
		tmp = tmp->next;
	}
	return ((t_var *)var);
}

t_env	ft_getenv(char **env)
{
	t_env	envp;

	envp = ft_init_env(env);
	envp.var = ft_init_var(&envp.list);
	return (envp);
}
