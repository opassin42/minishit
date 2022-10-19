/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 04:45:05 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/13 07:04:50 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_alnum_underscore(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	check_simple_quotes(char *s)
{
	if (*s == '\'')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_get_dollar_pos(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '$')
		++i;
	return (i);
}

void	expand_flag(t_list *token)
{
	char	*s;

	s = (char *)token->val;
	if (!check_simple_quotes(s) && ft_strchr(s, '$'))
		token->exp_flag = 1;
	else
		token->exp_flag = 0;
	return ;
}

char	*ft_extract_value(t_env envp, char *name)
{
	t_var	*var;

	var = envp.var;
	if (!name)
		return (NULL);
	while (var)
	{
		if (!ft_strcmp(var->name, name))
			return (var->value);
		var = var->next;
	}
	return (NULL);
}
