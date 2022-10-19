/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 22:25:14 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/13 06:48:50 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** 0 if there are only spaces
** 1 else
*/
int	ft_not_only_space(void *p)
{
	char	*tmp;

	tmp = (char *)p;
	if (!p)
		return (EXIT_SUCCESS);
	while (*tmp)
	{
		if (*tmp != ' ')
			return (EXIT_FAILURE);
		++tmp;
	}
	return (EXIT_SUCCESS);
}

static void	ft_reduce_spaces(t_list **token)
{
	t_list	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (!ft_not_only_space(tmp->val))
			tmp->val = " ";
		tmp = tmp->next;
	}
}

void	*ft_lexer(void *arg)
{
	t_list	*token;

	if (!arg)
		return (NULL);
	token = (t_list *)ft_tokeniser(arg, M_CHAR);
	if (!token)
		return (NULL);
	ft_reduce_spaces(&token);
	return (ft_type(&token), token);
}
	