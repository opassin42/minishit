/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recompose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 08:11:34 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/14 05:43:10 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*substring(t_env *envp, char *s)
{
	char	*tmp;

	(void)envp;
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
