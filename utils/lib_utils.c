/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 05:37:44 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/17 19:16:13 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_isalnum(int a)
{
	if ((a >= 65 && a <= 90) || (a >= 97 && a <= 122))
		return (1);
	return (0);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s != 0)
		write(fd, s, ft_strlen(s));
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}
