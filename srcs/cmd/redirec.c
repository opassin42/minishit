/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 05:04:34 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/12 03:58:09 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	rd_in(t_cmd *cmd)
{
	if (cmd->hdoc)
		printf("heredoc detected\n");
	else
		cmd->ret = open(cmd->infile, O_RDONLY, 0666);
	cmd->finalfdin = dup(STDIN_FILENO);
	if (cmd->ret == -1)
		return (EXIT_FAILURE);
	dup2(cmd->ret, cmd->fd_in);
	return (EXIT_SUCCESS);
}

int	rd_out(t_cmd *cmd)
{
	if (!cmd->append)
		cmd->ret = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		cmd->ret = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
	cmd->finalfdout = dup(STDOUT_FILENO);
	if (cmd->ret == -1)
		return (EXIT_FAILURE);
	dup2(cmd->ret, cmd->fd_out);
	return (EXIT_SUCCESS);
}
