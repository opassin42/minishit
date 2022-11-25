/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 04:45:05 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/25 01:14:19 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	hashing(char *s, int c, int factor)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (factor < 0)
		{
			if ((int)s[i] > 0 && (int)s[i] != c)
				s[i] = (int)s[i] * factor;
		}	
		else
			if ((int)s[i] < 0)
				s[i] = (int)s[i] * -factor;
		++i;
	}
}

int	ft_alnum_underscore(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	check_quotes(char *s, int c)
{
	if (*s == c)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_get_dollar_pos(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			break ;
		++i;
	}
	return (i);
}

void	expand_quote_flag(t_list *token)
{
	char	*s;

	s = (char *)token->val;
	token->quote = 0;
	token->exp_flag = 0;
	if (ft_strchr(s, '$') && *(s + 1))
	{
		if (!check_quotes(s, '\''))
			token->exp_flag = 1;
	}
	if (check_quotes(s, '"') || check_quotes(s, '\''))
		token->quote = 1;
	return ;
}
