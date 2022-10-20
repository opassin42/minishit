/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 08:12:19 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/20 08:13:41 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_heredoc(t_list *token)
{
	if (token->type == RD && ft_strcmp(token->val, "<<"))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	is_rd_in(t_list *token)
{
	if (token->type == RD && ft_strcmp(token->val, "<"))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	is_rd_out(t_list *token)
{
	if (token->type == RD && ft_strcmp(token->val, ">"))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	is_append(t_list *token)
{
	if (token->type == RD && ft_strcmp(token->val, ">>"))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	is_pipes(t_list *token)
{
	if (token->type == PIPE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
