/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opassin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 03:21:16 by opassin           #+#    #+#             */
/*   Updated: 2022/10/23 16:09:39 by opassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "../../include/minishell.h"

/*
 * is_n_opt : check les arguments
 * Type        : integer
 * Parametre : chaine de caracteres
 * Valeur de retrour : -1 en cas d'erreur (FAIL), 0 en cas de success (SUCCESS)
 */
int	is_n_opt(char *str)
{
	size_t	i;

	i = 0;
	if (str[0] != '-')
		return (0);
	else
	{
		while (str[++i])
		{
			if (str[i] != 'n')
				return (FAIL);
		}
	}
	return (SUCCESS);
}

/*
 * echo        : write arguments to standard output
 * Type        : integer
 * Parametre : double tableau de caracteres,
 la premiere case etant reserver
 on recoit ++arg en parametre
 * Valeur de retour : 1 en cas d'erreur, 0 en cas de succes
 */
int	ft_echo(char **arg)
{
	int	nflag;

	nflag = 0;
	while (is_n_opt(*(++arg)) == SUCCESS)
		nflag = 1;
	while (*arg != NULL)
		printf("%s", *arg++);
	if (!nflag)
		printf("\n");
	return (SUCCESS);
}
