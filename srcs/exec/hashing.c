/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 23:14:35 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/31 00:42:40 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	hashing(char *s, int c, int factor)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((int)s[i] > 0 && ((int)s[i] != c))// || (int)s[i] != '\t'))
			s[i] = (int)s[i] * factor;
		++i;
	}
}

void	positive_hashing(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((int)s[i] < 0)
			s[i] = (int)s[i] * -1;
		++i;
	}
}

void	hash_token(t_list *token)
{
	while (token)
	{
		positive_hashing(token->val);
		token = token->next;
	}
}

void	hash_quote(t_list **token, int flag)
{
	t_list	*tmp;

	tmp = *token;
	while (tmp)
	{
		// printf("expand = %s.\n", tmp->expand);
		if (tmp->quote && tmp->expand[0])
			hashing(tmp->expand, 0, flag);
		// printf("expand2 = %s.\n", tmp->expand);
		tmp = tmp->next;
	}
}
