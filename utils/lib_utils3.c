/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 03:29:08 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/14 06:36:42 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_is_space(int c)
{
	if (c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v'
		|| c == 32)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_isalnum(int a)
{
	if ((a >= 65 && a <= 90) || (a >= 97 && a <= 122))
		return (1);
	return (0);
}

int	ft_is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}


int	ft_isalpha(int c)
{
	return (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')));
}

/*
** Return 1 if there is another char than a white-space
** Else returns 0 (only white-spaces)
*/
int	ft_white_spaces(void *p)
{
	char	*tmp;

	tmp = (char *)p;
	if (!p)
		return (EXIT_SUCCESS);
	while (*tmp)
	{
		if (*tmp && !ft_is_space(*tmp))
			return (EXIT_FAILURE);
		++tmp;
	}
	return (EXIT_SUCCESS);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*a_s;
	size_t	len;

	if (!set || !s1)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (len && ft_strchr(set, s1[len]))
		len--;
	a_s = ft_substr((char *)s1, 0, len + 1);
	return (a_s);
}
