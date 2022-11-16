/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_compose.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 04:59:44 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/16 06:30:37 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
			return (val);
		}
		return (s);
	}
	return (s);
}

char	*ft_decompose(t_env envp, char *val)
{
	char	*exp;
	char	**tmp;

	if (!val)
		return (NULL);
	exp = expand(envp, val);
	if (!exp)
		return (ft_strdup(""));
	tmp = ft_split(exp, ' ');
	if (!tmp)
		return (NULL);
	return (*tmp);
}

char	*ft_assemble(t_env envp, t_list *token, char *first_val)
{
	char	*tmp;

	tmp = NULL;
	if (token->quote)
		tmp = ft_recompose(envp, first_val);
	else if (!token->quote)
		tmp = ft_decompose(envp, first_val);
	if (tmp)
		return (tmp);
	return (NULL);
}
