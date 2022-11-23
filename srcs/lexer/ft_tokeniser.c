/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokeniser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:19:11 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/23 20:37:21 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	hashing(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != c)
			s[i] = (int)s[i] * -1;
		++i;
	}
}

void	*inside_quotes(char *s, char *delim)
{
	int		i;
	char	*tmp;
	char	*name;

	i = 0;
	while (s[i] && s[i] != '$')
		++i;
	tmp = ft_substr(s, 0, i);
	if (!tmp)
		return (NULL);
	hashing(tmp, ' ');
	name = var_name(&s[i], i);
	if (!name)
		return (NULL);
	if (s[i] == '$')
	{

	}
		++i;

	return ((void *)s);
}

static void	*ft_token(char *s, char *m_char)
{
	char	*tmp;

	if (!s || !m_char)
		return (NULL);
	if (*s == '$')
		tmp = ft_dollar_char(s);
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
