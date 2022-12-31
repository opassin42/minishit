/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 05:04:34 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/28 21:27:37 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	rd_in(t_cmd *cmd)
{
	if (cmd->hdoc)
		printf("heredoc detected\n");
	else
		cmd->ret = open(cmd->infile, O_RDONLY, 0666);
	cmd->fd_in = dup(STDIN_FILENO);
	if (cmd->ret == -1)
		return (errno);
	dup2(cmd->ret, STDIN_FILENO);
	return (EXIT_SUCCESS);
}

int	rd_out(t_cmd *cmd)
{
	if (!cmd->append)
		cmd->ret = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		cmd->ret = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
	cmd->fd_out = dup(STDOUT_FILENO);
	if (cmd->ret == -1)
		return (errno);
	dup2(cmd->ret, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
