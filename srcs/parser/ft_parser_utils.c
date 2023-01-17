/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:04:56 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/17 18:12:56 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_check_quotes(t_list *token)
{
	char	*s;

	s = (char *)token->val;
	if (ft_flag_char(*s, QUOTE_LIST))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_open_quotes(t_list *token)
{
	char	*s;

	s = (char *)token->val;
	if (ft_flag_char(s[0], QUOTE_LIST))
		if (s[0] != s[ft_strlen(s) - 1])
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_quotes_word(t_list *token)
{
	if (ft_check_quotes(token))
	{
		if (ft_open_quotes(token) || ft_strlen((char *)token->val) == 1)
		{
			syntax_error("quote", ERRNO_1, 2, ft_putstr_fd);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
