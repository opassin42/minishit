/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 03:21:16 by opassin           #+#    #+#             */
/*   Updated: 2022/10/25 00:24:30 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * is_n_opt : check les arguments
 * Type        : integer
 * Parametre : chaine de caracteres
 * Valeur de retrour : -1 en cas d'erreur (FAIL), 0 en cas de success (SUCCESS)
 */
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
 * echo        : write arguments to standard output
 * Type        : integer
 * Parametre : double tableau de caracteres,
 la premiere case etant reserver
 on recoit ++arg en parametre
 * Valeur de retour : 1 en cas d'erreur, 0 en cas de succes
 */
int	ft_echo(t_env *envp, t_cmd *cmd)
{
	int		nflag;
	char	**arg;

	(void)envp;
	arg = cmd->arg;
	nflag = 0;
	if (!arg)
		return (printf("\n"), EXIT_SUCCESS);
	while (*arg)
	{
		if (is_n_opt(*arg) == EXIT_SUCCESS)
		{
			nflag = 1;
			arg++;
		}
		else
			break ;
	}
	while (*arg != NULL)
	{	
		printf("%s", *(arg++));
		if (*arg != NULL)
			printf(" ");
	}
	if (!nflag)
		printf("\n");
	return (EXIT_SUCCESS);
}
