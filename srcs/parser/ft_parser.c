/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:30:05 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/23 16:22:02 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** New token list without void node (node with only space(s))
** Find a better way not to suppress spaces between 2 quotes
*/
void	*ft_void_skipper(t_list **token)
{
	void	*a_s;
	t_list	*tmp;
	t_list	*d_token;

	tmp = *token;
	a_s = tmp->val;
	d_token = ft_lstnew(a_s);
	if (!d_token)
		return (NULL);
	tmp = tmp->next;
	while (tmp)
	{
		a_s = tmp->val;
		if (ft_not_only_space(a_s))
			ft_lstadd_back(&d_token, ft_lstnew(a_s));
		tmp = tmp->next;
	}
	return (ft_free_token(token, free), (void *)d_token);
}

int	ft_parser(t_list **token)
{
	t_list		*tmp;
	t_syntaxer	syntax;

	tmp = *token;
	init_syntaxer(syntax);
	if (ft_syntaxer(&tmp, syntax))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
