/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 05:04:34 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/26 22:35:22 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	rd_in(t_cmd *cmd)
{
	int	infd;

	infd = 0;
	if (cmd->hdoc)
		printf("heredoc detected\n");
	else
		infd = open(cmd->infile, O_RDONLY);
	if (infd < 0)
		return (errno);
	dup2(infd, STDIN_FILENO);
	close(infd);
	return (EXIT_SUCCESS);
}

int	rd_out(t_cmd *cmd)
{
	int	outfd;

	if (!cmd->append)
		outfd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		outfd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfd < 0)
		return (errno);
	dup2(outfd, STDOUT_FILENO);
	close(outfd);
	return (EXIT_SUCCESS);
}
