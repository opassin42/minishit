/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 06:36:46 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/27 22:36:54 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_flag_char(int c, char *m_char)
{
	if (ft_strchr(m_char, c))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
** Seems like i have some invalid reead of size 1
** Because of this function ??
*/
void	*ft_meta_quotes(char *s, int c)
{
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	if (s[++i])
		while (s[i] && s[i] != c)
			++i;
	return ((void *)ft_substr(s, 0, i + 1));
}

/*
** Specially for spaces and pipes
*/
void	*ft_meta_char(char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	if (!ft_flag_char(c, QUOTE_LIST))
	{
		i = 0;
		while (s[i++])
			if (s[i] != (char)c)
				break ;
		return ((void *)ft_substr(s, 0, i));
	}
	else
		return (ft_meta_quotes(s, c));
	return ((void *)s);
}

void	*ft_dollar_char(char *s)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
		// return ((void *)ft_substr(s, 0, i + 1));
	while (s[i++])
	{
		if (s[i] == '$' && s[i + 1] && ft_is_digit(s[i + 1]))
			break ;
		if (i == 2 && ft_is_digit(s[i]))
			break ;
		if (ft_alnum_underscore(s[i]))
			break ;
	}
	return ((void *)ft_substr(s, 0, i));
}

void	*ft_normal_char(char *s, char *m_char)
{
	int	i;

	if (!s || !m_char)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (ft_flag_char(s[i], m_char) || s[i] == '$')
			break ;
		++i;
	}
	return ((void *)ft_substr(s, 0, i));
}
