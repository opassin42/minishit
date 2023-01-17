/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 22:25:14 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/17 18:08:51 by ccouliba         ###   ########.fr       */
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

	if (!p)
		return (EXIT_SUCCESS);
	tmp = (char *)p;
	while (*tmp)
	{
		if (*tmp != ' ')
			return (EXIT_FAILURE);
		++tmp;
	}
	return (EXIT_SUCCESS);
}

static void	reduce_spaces(t_list **token)
{
	t_list	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (!ft_not_only_space(tmp->val))
		{
			tmp->val = ft_strdup(" ");
			if (!tmp->val)
				return ;
		}
		tmp = tmp->next;
	}
}

static void	prev_last_is_last(t_list **token, t_type type)
{
	t_list	*tmp;
	t_list	*last;

	tmp = *token;
	last = ft_lstlast(tmp);
	if (last && last->type == type)
		ft_lst_prevlast(&tmp);
	return ;
}

void	*ft_lexer(void *arg)
{
	t_list	*token;

	if (!arg)
		return (NULL);
	token = (t_list *)ft_tokeniser(arg, M_CHAR);
	if (!token)
		return (NULL);
	reduce_spaces(&token);
	ft_type(&token);
	return (prev_last_is_last(&token, VOID), token);
}
