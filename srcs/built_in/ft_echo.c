/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 03:48:18 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/14 04:24:35 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_n_opt(char *str)
{
	size_t	i;

	i = 0;
	if (str[0] != '-')
		return (EXIT_FAILURE);
	else
	{
		while (str[++i])
		{
			if (str[i] != 'n')
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

/*
 * echo        : write paramuments to standard output
 * Type        : integer
 * Parametre : double tableau de caracteres,
 la premiere case etant reserver
 on recoit ++param en parametre
 * Valeur de retour : 1 en cas d'erreur, 0 en cas de succes
 */

int	ft_echo(t_env *envp, t_cmd *cmd)
{
	int		nflag;
	char	**param;

	(void)envp;
	param = cmd->param;
	if (!param || !*param)
		return (printf("\n"), EXIT_SUCCESS);
	nflag = 0;
	while (*param)
	{
		while (*param && (is_n_opt(*param) == EXIT_SUCCESS))
		{
			nflag = 1;
			param++;
		}
		while (*param != NULL)
		{	
			printf("%s", *(param++));
			if (*param != NULL)
				printf(" ");
		}
	}
	if (!nflag)
		printf("\n");
	return (EXIT_SUCCESS);
}
