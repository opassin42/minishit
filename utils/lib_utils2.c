/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:20:26 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/17 19:17:11 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

char	*ft_substr(char *s, int begin, size_t len)
{
	size_t	i;
	char	*sub;

	if (!s)
		return (gc_free(), NULL);
	sub = push_top(&g_data.gc, sizeof(char) * (len + 1));
	if (!sub)
		return (gc_free(), NULL);
	i = 0;
	while (s[begin] && i != len)
		sub[i++] = s[begin++];
	sub[i] = '\0';
	return (sub);
}

char	*ft_strdup(char *s)
{
	int		i;
	char	*dup;

	if (!s)
		return (malloc(0));
	dup = (char *)push_top(&g_data.gc, sizeof(char) * (ft_strlen(s) + 1));
	if (!dup)
		return (gc_free(), NULL);
	i = -1;
	while (s[++i])
		dup[i] = s[i];
	dup[i] = '\0';
	return (dup);
}

char	*ft_strchr(char *s, int c)
{
	char	*tmpsrc;

	if (!s)
		return (NULL);
	tmpsrc = (char *)s;
	while (*tmpsrc)
	{
		if (*tmpsrc == (char)c)
			return (tmpsrc);
		tmpsrc++;
	}
	if ((char)c == '\0' && *tmpsrc == '\0')
		return (tmpsrc);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)push_top(&g_data.gc, sizeof(char) * (len + 1));
	if (!join)
		return (gc_free(), NULL);
	else
	{
		ft_memcpy(join, s1, ft_strlen(s1));
		ft_memcpy(join + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	}
	return (join);
}
