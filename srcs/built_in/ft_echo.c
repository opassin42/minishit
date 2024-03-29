/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 03:48:18 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/17 18:49:06 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * is_n_opt     : check if the n option is present
 * Type        : static integer
 * Parameter   : string
 * Return value : 1 in case of error or 0 in case of success
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

static void	check_for_flag(int nflag)
{
	if (!nflag)
		printf("\n");
}

/*
 * ft_echo     : write paramuments to standard output
 * Type        : integer
 * Parameter   : the environment, the cmd list
 * Return value : 1 en cas d'erreur, 0 en cas de succes
 */
int	ft_echo(t_env *envp, t_cmd *cmd)
{
	int		nflag;
	char	**param;

	(void)envp;
	param = cmd->param;
	if ((!param || !*param))
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
	return (check_for_flag(nflag), EXIT_SUCCESS);
}
