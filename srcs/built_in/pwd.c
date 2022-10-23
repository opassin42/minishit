/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opassin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 03:21:16 by opassin           #+#    #+#             */
/*   Updated: 2022/10/23 12:58:49 by opassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

/*
 * PWD  		: print Working Directory 
 * Type 		: integer
 * Parametre	: aucun
 * Valeur de retour:  errno en cas d'erreur, zero en cas de succes;
 */
int	pwd(void)
{
	char	buff[PATH_MAX];

	if (getcwd(buff, sizeof(buff)) == NULL)
	{
		printf("error: %s", strerror(errno));
		return (errno);
	}
	else
		printf("%s\n", buff);
	return (0);
}
