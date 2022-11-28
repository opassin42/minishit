/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recompose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 08:11:34 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/26 01:51:31 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** hav to hash every char of te returned val if there is quotes
*/
char	*remove_quotes(t_list *token)
{
	char	*s;
	char	*val;

	s = (char *)token->val;
	if (!s)
		return (NULL);
	if (ft_strlen(s) == 2 && ft_strchr(QUOTE_LIST, s[0]) && s[0] == s[1])
		return (ft_strdup(""));
	else
	{
		if (ft_strchr(QUOTE_LIST, s[0]))
		{
			val = ft_substr(s, 1, ft_strlen(s) - 2);
			if (!val)
				return (NULL);
			return (val);
		}
		return (s);
	}
	return (s);
}

static char	*substring(t_env envp, char *s)
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

/*
** Have to hash the returned value except space
*/
static char	*replace(t_env envp, char *val)
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

char	*ft_recompose(t_env envp, char *s)
{
	char	*tmp;
	char	*val;
	char	*join;

	if (!s)
		return (NULL);
	tmp = substring(envp, s);
	if (!tmp)
		return (NULL);
	val = replace(envp, tmp);
	if (!val)
		return (NULL);
	if (!*val)
		join = val;
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

/*
** NEW VERSION
*/
