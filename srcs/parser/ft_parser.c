/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:30:05 by ccouliba          #+#    #+#             */
/*   Updated: 2022/09/28 01:38:15 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_right_pipe(t_list *token)
{
	if (token->type == PIPE)
		if (ft_strlen((char *)token->val) != 1)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_right_rd(t_list *token)
{
	if (token->type == RD)
	{
		if (ft_strlen((char *)token->val) > 2)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_check_quotes_word(t_list *token)
{
	if (ft_check_quotes(token))
	{
		if (ft_open_quotes(token) || ft_strlen((char *)token->val) == 1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_syntaxer(t_list *token)
{
	if (token->type == PIPE || token->type == RD)
		if (token->next->type == PIPE || token->next->type == RD)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
** maybe replace return(FAIL) by exit(FAIL) ??
*/
int	ft_parser(t_list **token)
{
	t_list	*tmp;

	tmp = (t_list *)(*token);
	if (ft_check_last_token(tmp))
		return (EXIT_FAILURE);
	while (tmp)
	{
		if (tmp && tmp->next && ft_syntaxer(tmp))
			return (ft_free_token(token, free), EXIT_FAILURE);
		if (ft_right_pipe(tmp) || ft_right_rd(tmp))
			return (ft_free_token(token, free), EXIT_FAILURE);
		if (ft_check_quotes_word(tmp))
			return (ft_free_token(token, free), EXIT_FAILURE);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
