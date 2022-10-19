/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 17:35:35 by ccouliba          #+#    #+#             */
/*   Updated: 2022/09/26 18:20:58 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** 0 if the first char of a token is NOT a quote
** 1 else
*/
int	ft_check_quotes(t_list *token)
{
	char	*tmp;

	tmp = (char *)token->val;
	if (ft_flag_char(tmp[0], QUOTE_LIST))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
** 0 if the quotes are well closed
** 1 else
*/
int	ft_open_quotes(t_list *token)
{
	char	*tmp;

	tmp = (char *)token->val;
	if (ft_strlen(tmp))
		if (tmp[0] != tmp[ft_strlen(tmp) - 1])
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	*ft_rm_quotes(t_list *token)
{
	char	*tmp;

	if (ft_check_quotes(token))
	{
		tmp = (char *)token->val;
		if (!ft_open_quotes(token) && ft_strlen(tmp) > 2)
			return ((void *)ft_substr(tmp, 1, ft_strlen(tmp) - 2));
	}
	return (token->val);
}

void	ft_quotes(t_list **token)
{
	t_list	*tmp;

	tmp = *token;
	while (tmp)
	{
		tmp->val = ft_rm_quotes(tmp);
		tmp = tmp->next;
	}
}
