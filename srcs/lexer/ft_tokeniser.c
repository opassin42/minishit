/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokeniser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:19:11 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/19 20:26:39 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	*ft_fill_token(char *s, char *m_char)
{
	char	*tmp;

	if (!s)
		return (NULL);
	if (*s == '$')
		tmp = ft_dollar_char(s);
	else if (ft_flag_char(*s, m_char))
		tmp = ft_meta_char(s, *s);
	else
		tmp = ft_normal_char(s, m_char);
	return ((void *)tmp);
}

void	*ft_tokeniser(void *arg, char *m_char)
{
	char	*s;
	void	*tmp;
	t_list	*token;

	if (!arg || !m_char)
		return (NULL);
	s = (char *)arg;
	tmp = ft_fill_token(s, m_char);
	if (tmp)
	{
		token = ft_lstnew(tmp);
		if (!token)
			return (NULL);
	}
	s = s + ft_strlen((char *)tmp);
	while (*s)
	{
		tmp = NULL;
		tmp = ft_fill_token(s, m_char);
		if (tmp)
			ft_lstadd_back(&token, ft_lstnew(tmp));
		s = s + ft_strlen((char *)tmp);
	}
	return ((void *)token);
}
