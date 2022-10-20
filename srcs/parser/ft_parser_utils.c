/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:04:56 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/20 09:41:40 by ccouliba         ###   ########.fr       */
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
