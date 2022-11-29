/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokeniser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:19:11 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/29 04:11:10 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	*ft_token(char *s, char *m_char)
{
	char	*tmp;

	if (!s || !m_char)
		return (NULL);
	if (ft_flag_char(*s, m_char))
		tmp = ft_meta_char(s, *s);
	else
		tmp = ft_normal_char(s, m_char);
	if (tmp)
		return ((void *)tmp);
	return (NULL);
}

void	*ft_tokeniser(void *arg, char *m_char)
{
	char	*s;
	void	*tmp;
	t_list	*token;

	if (!arg || !m_char)
		return (NULL);
	s = (char *)arg;
	tmp = ft_token(s, m_char);
	if (!tmp)
		return (NULL);
	token = ft_lstnew(tmp);
	if (!token)
		return (NULL);
	s = s + ft_strlen((char *)tmp);
	while (*s)
	{
		tmp = NULL;
		tmp = ft_token(s, m_char);
		if (!tmp)
			return (NULL);
		ft_lstadd_back(&token, ft_lstnew(tmp));
		s = s + ft_strlen((char *)tmp);
	}
	return ((void *)token);
}
