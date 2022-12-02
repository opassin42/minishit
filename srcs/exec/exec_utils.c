/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:21:28 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/01 07:54:03 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute(t_env *envp, t_cmd *cmd, int fd, int (*f)())
{
	int	ret;

	dup2(fd, STDIN_FILENO);
	close(fd);
	ret = f(envp, cmd);
	return (ret);
}

int	ft_pipe(t_env *envp, t_cmd *cmd)
{
	int	tmp;
	int	ret;
	int	fd[2];

	ret = 0;
	if (cmd->next)
	{
		tmp = dup(STDIN_FILENO);
		pipe(fd);
		{
			if (fork() == -1)
				return (EXIT_FAILURE);
			if (fork() == 0)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				close(fd[0]);
				ret = execute(envp, cmd, tmp, ft_router);
			}
			else
			{
				close(tmp);
				close(fd[1]);
				wait(NULL);
				tmp = fd[0];
				return (ret);
			}
		}
	}
	return (EXIT_SUCCESS);
}
