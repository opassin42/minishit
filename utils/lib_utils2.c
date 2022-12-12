/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:20:26 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/12 07:23:20 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Seems like i have some invalid reead of size 1
** Because of this function ??
*/
char	*ft_substr(char *s, int begin, size_t len)
{
	size_t	i;
	char	*sub;

	if (!s)
		return (NULL);
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

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}

void	*ft_memmove(void *dest, void *src, size_t n)
{
	unsigned char	*a_dest;
	unsigned char	*a_src;

	a_dest = (unsigned char *)dest;
	a_src = (unsigned char *)src;
	if (src < dest)
	{
		while (n != 0)
		{
			a_dest[n - 1] = a_src[n - 1];
			n--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
