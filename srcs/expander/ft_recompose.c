/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recompose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 08:11:34 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/24 06:56:29 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	hashing(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != c)
			s[i] = (int)s[i] * -1;
		++i;
	}
}

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

static char	*substring(t_env envp, char *s)
{
	char	*tmp;

	(void)envp;
	if (*s == '$')
		tmp = ft_dollar_char(s);
	else
		tmp = normal_substring(s);
	if (!tmp)
		return (NULL);
	return (tmp);
}

/*
** Have to hash the returned value except space
*/
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
		hashing(tmp, ' ');
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

/*
** NEW VERSION
*/
