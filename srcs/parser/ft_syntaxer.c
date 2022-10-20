/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntaxer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 00:51:18 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/20 09:43:00 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_check_last_token(t_list *token)
{
	t_list	*last;

	last = ft_lstlast(token);
	if (last->type == PIPE || last->type == RD)
		return (EXIT_FAILURE);
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

int	check_syntax(t_list *token, t_syntaxer synt)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (synt[i](token))
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}

int	ft_syntaxer(t_list **token, t_syntaxer synt)
{
	t_list		*tmp;

	tmp = (t_list *)(*token);
	if (ft_check_last_token(tmp))
		return (EXIT_FAILURE);
	while (tmp)
	{
		if (check_syntax(tmp, synt))
			return (EXIT_FAILURE);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
