/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntaxer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 00:51:18 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/23 16:23:42 by ccouliba         ###   ########.fr       */
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

int	check_syntax(t_list *token, t_syntaxer synt)
{
	int	i;
	int	ret;

	i = 0;
	while (i < 4)
	{
		ret = synt[i](token);
		if (ret)
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
