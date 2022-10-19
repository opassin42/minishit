/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 05:37:44 by ccouliba          #+#    #+#             */
/*   Updated: 2022/09/17 04:43:49 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	char	*a_s;

	a_s = (char *)s;
	while (*a_s && *a_s != c)
			a_s++;
	if (*a_s == c)
		return (a_s);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	join = malloc(sizeof(char) * (len + 1));
	if (!join)
		return (0);
	else
	{
		ft_memcpy(join, s1, ft_strlen(s1));
		ft_memcpy(join + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	}
	return (join);
}

void	*ft_strjoin_char(char *s1, char c)
{
	int		i;
	int		len;
	char	*tab;

	i = 0;
	len = ft_strlen(s1);
	tab = (char *)malloc(sizeof(char) * (len + 2));
	if (!tab || s1)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		tab[i] = s1[i];
		i++;
	}
	if (c)
		tab[i++] = c;
	tab[i] = '\0';
	return (tab);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*a_s;

	a_s = (unsigned char *)s;
	while (n != 0)
	{
		*(a_s++) = (unsigned char)c;
		n--;
	}
	return (s);
}
