/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_compose.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 04:59:44 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/24 06:56:54 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** hav to hash every char of te returned val if there is quotes
*/
char	*remove_quotes(t_list *token)
{
	char	*s;
	char	*val;

	s = (char *)token->val;
	if (!s)
		return (NULL);
	if (ft_strlen(s) == 2 && ft_strchr(QUOTE_LIST, s[0]) && s[0] == s[1])
		return (ft_strdup(""));
	else
	{
		if (ft_strchr(QUOTE_LIST, s[0]))
		{
			val = ft_substr(s, 1, ft_strlen(s) - 2);
			if (!val)
				return (NULL);
			hashing(val, 0);
			return (val);
		}
		return (s);
	}
	return (s);
}
