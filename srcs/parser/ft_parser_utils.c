/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:04:56 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/23 16:23:51 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_quotes_word(t_list *token)
{
	if (ft_check_quotes(token))
	{
		if (ft_open_quotes(token) || ft_strlen((char *)token->val) == 1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	wrong_next(t_list *token)
{
	if (token->type == PIPE || token->type == RD)
		if (token->next->type == PIPE || token->next->type == RD)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	wrong_pipe(t_list *token)
{
	if (token->type == PIPE)
		if (ft_strlen((char *)token->val) != 1)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	wrong_rd(t_list *token)
{
	if (token->type == RD)
	{
		if (ft_strlen((char *)token->val) > 2)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_syntaxer(t_syntaxer synt)
{
	synt[0] = wrong_next;
	synt[1] = wrong_pipe;
	synt[2] = wrong_rd;
	synt[3] = check_quotes_word;
	return (EXIT_SUCCESS);
}
