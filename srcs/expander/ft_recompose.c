/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recompose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 08:11:34 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/17 02:09:21 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*normal_substring(char *s)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			break ;
		++i;
	}
	return (ft_substr(s, 0, i));
}

static char	*dollar_substring(char *s)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[++i])
	{
		if (i == 1 && (s[i] == '?' || ft_is_digit(s[i])))
			return (ft_substr(s, 0, i + 1));
		else if (ft_alnum_underscore(s[i]))
			break ;
	}
	return (ft_substr(s, 0, i));
}

static char	*substring(t_env envp, char *s)
{
	char	*tmp;

	(void)envp;
	if (*s == '$')
		tmp = dollar_substring(s);
	else
		tmp = normal_substring(s);
	if (!tmp)
		return (NULL);
	return (tmp);
}

static char	*compose(t_env envp, char *val)
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
	val = compose(envp, tmp);
	if (!val)
		return (NULL);
	join = val;
	s = s + ft_strlen(tmp);
	while (*s)
	{
		tmp = substring(envp, s);
		if (!tmp)
			return (NULL);
		join = ft_strjoin(join, compose(envp, tmp));
		if (!join)
			return (NULL);
		s = s + ft_strlen(tmp);
	}
	return (join);
}
