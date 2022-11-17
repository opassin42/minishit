/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:30:05 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/15 17:13:32 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	init_syntaxer(t_syntaxer synt)
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
		return (g_status = 2);
	return (EXIT_SUCCESS);
}
