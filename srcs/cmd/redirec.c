/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 05:04:34 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/02 09:35:04 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	rd_out(t_cmd *cmd, int mod)
// {
// 	int	ret;

// 	ret = open(cmd->outfile, mod);
// 	if (ret == -1)
// 		return (errno);
// 	cmd->fd_out = ret;
// 	return (EXIT_SUCCESS);
// }

// int	rd_in(t_cmd *cmd)
// {
// 	int	ret;

// 	if (!cmd->infile)
// 		return (EXIT_FAILURE);
// 	if (access(cmd->infile, F_OK))
// 		return (perror((const char *)cmd->infile), errno);
// 	if (access(cmd->infile, R_OK))
// 		return (perror((const char *)cmd->infile), errno);
// 	ret = open(cmd->infile, O_RDONLY);
// 	if (ret == -1)
// 		return (errno);
// 	cmd->fd_in = ret;
// 	return (EXIT_SUCCESS);
// }

// int	ft_rd(t_cmd *cmd)
// {
// 	if (cmd->outfile)
// 	{
// 		if (cmd->append)
// 			cmd->fd_out = open(cmd->outfile, O_APPEND);
// 		else
// 			cmd->fd_out = open(cmd->outfile, O_CREAT);
// 		if (cmd->fd_out == -1)
// 			return (errno);
// 	}
// 	return (EXIT_SUCCESS);
// }
