/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:30:05 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/01 04:08:16 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	wrong_next(t_list *token)
{
	if (token->type == PIPE || token->type == RD)
	{
		if (token->next->type == PIPE || token->next->type == RD)
		{
			syntax_error((char *)token->val, ERRNO_1, 2, ft_putstr_fd);
			return (EXIT_FAILURE);
		}
		if (token->next->type == VOID)
		{
			if (token->next->next->type == RD
				|| token->next->next->type == PIPE)
			{
				syntax_error((char *)token->val, ERRNO_1, 2, ft_putstr_fd);
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}

static int	wrong_pipe(t_list *token)
{
	if (token->type == PIPE)
	{
		if (ft_strlen((char *)token->val) != 1)
		{
			syntax_error("pipeline", ERRNO_1, 2, ft_putstr_fd);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

static int	wrong_rd(t_list *token)
{
	if (token->type == RD)
	{
		if (ft_strlen((char *)token->val) > 2)
		{
			syntax_error(token->val, ERRNO_1, 2, ft_putstr_fd);
			return (EXIT_FAILURE);
		}
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

/*
** Take address of token
** Run a syntaxer
** Return 0 or 2
*/
int	ft_parser(t_list **token)
{
	t_list		*tmp;
	t_syntaxer	syntax;

	tmp = *token;
	init_syntaxer(syntax);
	if (ft_syntaxer(&tmp, syntax))
		return (2);
	return (EXIT_SUCCESS);
}
