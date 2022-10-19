/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:38:23 by ccouliba          #+#    #+#             */
/*   Updated: 2022/08/21 17:20:48 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** ECHO
** If no option (0 or 1) -> add a \n at the end of the printing
** Else no \n, just return
** Change ft_echo
*/
static int	print_string(char **string, int index)
{
	if (!string)
		return (EXIT_FAILURE);
	while (string[index++])
	{
		write(1, string[index], ft_strlen(string[index]));
		if (string[index + 1])
			write(1, " ", 1);
		else
			break ;
	}
	return (EXIT_SUCCESS);
}

/*
** Returns 1 if char isn't a minus
** Else returns 0
*/
static int	check_minus(int minus)
{
	if ((char)minus != '-')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
** Returns 1 if char isn't 'n'
** Else returns 0
*/
static int	check_option(int c)
{
	if ((char)c != 'n')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
** Returns 1 if wrong option
** Else returns 0
*/
static int	ft_option(char *s)
{
	if (!s || check_minus(*s))
		return (EXIT_FAILURE);
	while (*(++s))
	{
		if (check_option(*s))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_echo(char **string)
{
	int	i;
	int	option;

	if (!string)
		return (write(1, "\n", 1), EXIT_SUCCESS);
	i = 0;
	option = 0;
	while (string[++i])
	{
		if (i == 1 && !ft_option(string[i]))
		{
			option = 1;
			break ;
		}
		write(1, string[i], ft_strlen(string[i]));
		if (string[i + 1])
			write(1, " ", 1);
	}
	if (option)
		return (print_string(string, i), EXIT_SUCCESS);
	return (write(1, "\n", 1), EXIT_SUCCESS);
}
