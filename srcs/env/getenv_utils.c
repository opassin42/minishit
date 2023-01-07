/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 03:28:46 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/07 00:55:24 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**when_no_env(void)
{
	char	*tmp;
	char	**env;

	env = (char **)push_top(&g_data.gc, sizeof(char *) * 3);
	if (!env)
		return (gc_free(), (char **) NULL);
	tmp = ft_strjoin("PWD=", get_pwd());
	if (!tmp)
		return ((char **) NULL);
	*env = ft_strdup(tmp);
	if (!*env)
		return ((char **) NULL);
	tmp = NULL;
	tmp = ft_strjoin("SHLVL=", "42");
	if (!tmp)
		return ((char **) NULL);
	*(env + 1) = ft_strdup(tmp);
	if (!*(env + 1))
		return ((char **) NULL);
	*(env + 2) = 0;
	return (env);
}

char	*ft_var_name(char *s)
{
	int	i;

	i = -1;
	if (!s)
		return (NULL);
	while (s[++i])
	{
		if (s[i] == '=')
			break ;
	}
	return (ft_substr(s, 0, i));
}

t_var	*ft_new_var(t_list *token)
{
	int		begin;
	char	*str;
	t_var	*var;

	str = (char *)token->val;
	var = push_top(&g_data.gc, sizeof(t_var));
	if (!var)
		return (gc_free(), NULL);
	var->name = ft_var_name(str);
	if (!var->name)
		return (NULL);
	begin = ft_strlen(var->name) + 1;
	var->value = ft_substr(str, begin, ft_strlen(str));
	if (!var->value)
		return (NULL);
	var->next = NULL;
	return (var);
}

t_var	*ft_last_var(t_var *var)
{
	if (var)
	{
		while (var->next)
			var = var->next;
	}
	return (var);
}

void	ft_var_addback(t_var **var, t_var *new_var)
{
	if (new_var)
	{
		if (*var)
			ft_last_var(*var)->next = new_var;
		else
			*var = new_var;
	}
}
