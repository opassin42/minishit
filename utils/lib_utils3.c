/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 03:29:08 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/06 04:32:35 by ccouliba         ###   ########.fr       */
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
