/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recompose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 08:11:34 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/20 03:09:35 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_value(t_env *envp, char *var_name)
{
	t_var	*var;

	if (envp)
	{
		if (!var_name || (*var_name == '$' && !(*var_name + 1)))
			return (NULL);
		var = envp->var;
		while (var)
		{
			if (var->name && !ft_strcmp(var->name, var_name))
			{
				if (var->value)
					return (var->value);
				else
					break ;
			}
			var = var->next;
		}
	}
	return (ft_strdup(""));
}

static char	*substring(t_env *envp, char *s)
{
	char	*tmp;

	(void)envp;
	if (!s)
		return (NULL);
	if (*s == '$')
		tmp = ft_dollar_char(s);
	else
		tmp = ft_normal_char(s, "$");
	if (!tmp)
		return (NULL);
	return (tmp);
}

static char	*replace(t_env *envp, char *val)
{
	char	*tmp;

	if (!val)
		return (NULL);
	tmp = NULL;
	if (*val == '$')
	{
		tmp = expand(envp, val);
		if (!tmp)
			return (ft_strdup(""));
	}
	else
		tmp = val;
	return (tmp);
}

char	*ft_recompose(t_env *envp, char *s)
{
	char	*tmp;
	char	*join;

	if (!s)
		return (NULL);
	tmp = substring(envp, s);
	if (!tmp)
		return (NULL);
	join = replace(envp, tmp);
	if (!join)
		return (NULL);
	s = s + ft_strlen(tmp);
	while (*s)
	{
		tmp = substring(envp, s);
		if (!tmp)
			return (NULL);
		join = ft_strjoin(join, replace(envp, tmp));
		if (!join)
			return (NULL);
		s = s + ft_strlen(tmp);
	}
	return (join);
}
