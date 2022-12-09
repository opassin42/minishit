/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 03:48:18 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/15 17:38:22 by ccouliba         ###   ########.fr       */
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
	if (!param || !*param)
		return (ft_putstr_fd("\n", cmd->fd_out), EXIT_SUCCESS);
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
			ft_putstr_fd(*(param++), cmd->fd_out);
			if (*param != NULL)
				ft_putstr_fd(" ", cmd->fd_out);
		}
	}
	if (!nflag)
		printf("\n");
	/*if (cmd->fd_out != 1)
			dup2(cmd->fd_out, STDOUT);
	if (cmd->fd_out != 1)
	{
		close(cmd->fd_in);
		close(cmd->fd_out);
	}*/
	return (EXIT_SUCCESS);
}
