/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 23:14:35 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/04 17:47:46 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	negative_hashing(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		if ((int)s[i] > 0 && ((int)s[i] != c))
			s[i] = (int)s[i] * -1;
		++i;
	}
}

void	positive_hashing(char *s, int c)
{
	int	i;

	i = 0;
	(void)c;
	if (!s)
		return ;
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
		positive_hashing(token->val, 0);
		token = token->next;
	}
}

void	hash_quote(t_list **token)
{
	t_list	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->quote && tmp->expand[0])
			negative_hashing(tmp->expand, 0);
		tmp = tmp->next;
	}
}
