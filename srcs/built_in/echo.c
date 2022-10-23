/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opassin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 03:21:16 by opassin           #+#    #+#             */
/*   Updated: 2022/10/23 13:00:43 by opassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

/*
 * is_n_opt : check les arguments
 * Type        : integer
 * Parametre : chaine de caracteres
 * Valeur de retrour : 0 en cas d'erreur (FALSE), 1 en cas de success (TRUE)
 */
int	is_n_opt(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	else
	{
		while (str[++i])
		{
			if (str[i] != 'n')
				return (0);
		}
	}
	return (1);
}

/*
 * echo        : write arguments to standard output
 * Type        : integer
 * Parametre : double tableau de caracteres,
 la premiere case etant reserver
 on recoit ++arg en parametre
 * Valeur de retour : 1 en cas d'erreur, 0 en cas de succes
 */
int	echo(char **arg)
{
	int	nflag;

	nflag = 0;
	while (is_n_opt(*(++arg)))
		nflag = 1;
	while (*arg != NULL)
		printf("%s", *arg++);
	if (!nflag)
		printf("\n");
	return (0);
}
