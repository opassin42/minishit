/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 03:21:16 by opassin           #+#    #+#             */
/*   Updated: 2022/12/12 03:43:57 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * PWD  		: print Working Directory 
 * Type 		: integer
 * Parameter	: lsit env, list cmd
 * Return value : errno in case of fail, 0 in case of succes;
 */
int	ft_pwd(t_env *envp, t_cmd *cmd)
{
	char	buff[PATH_MAX];

	(void)envp;
	if (!cmd->param)
	{
		if (getcwd(buff, sizeof(buff)) == NULL)
		{
			printf("error: %s", strerror(errno));
			return (errno);
		}
		else
			printf("%s\n", buff);
		return (EXIT_SUCCESS);
	}
	printf ("minishell: pwd: too many arguments\n");
	return (EXIT_FAILURE);
}

/*
 * get_pwd 		: return the current Working Directory 
 * Type 		: string
 * Parameter	: void
 * Return value : NULL in case of fail, current directory's
 * path in case of succes;
 */
char	*get_pwd(void)
{
	char	buff[PATH_MAX];

	if (getcwd(buff, sizeof(buff)) == NULL)
	{
		printf("error: %s", strerror(errno));
		return (NULL);
	}
	else
		return (ft_strdup(buff));
	return (NULL);
}
