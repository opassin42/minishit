/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 03:21:16 by opassin           #+#    #+#             */
/*   Updated: 2022/10/25 00:13:43 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * PWD  		: print Working Directory 
 * Type 		: integer
 * Parametre	: aucun
 * Valeur de retour:  errno en cas d'erreur, zero en cas de succes;
 */
int	ft_pwd(t_env *envp, t_cmd *cmd)
{
	char	buff[PATH_MAX];

	(void)envp;
	(void)cmd;
	if (getcwd(buff, sizeof(buff)) == NULL)
	{
		printf("error: %s", strerror(errno));
		return (errno);
	}
	else
		printf("%s\n", buff);
	return (0);
}
