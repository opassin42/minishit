/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 00:00:49 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/18 23:02:42 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*var_name(char *str, int start)
{
	int	i;

	if (!str)
		return (NULL);
	i = start + 1;
	while (str[i])
	{
		if (ft_alnum_underscore(str[i]))
			return ((void *)ft_substr(str, start, i - start));
		++i;
	}
	return (NULL);
}

void	*var_value(t_env envp, char *name)
{
	char	*tmp;

	if (!name)
		return (NULL);
	tmp = ft_extract_value(envp, name);
	if (!tmp)
		return (ft_strdup(""));
	return (tmp);
}

static char	*check_name(char *name)
{
	char	*tmp;

	if (!name)
		return (NULL);
	tmp = NULL;
	if (*(name + 1))
		tmp = name + 1;
	else
		tmp = ft_strdup("");
	return (tmp);
}

/*
**
*/
static char	*expand(t_env envp, char *s)
{
	int		i;
	char	*name;
	char	*value;

	i = ft_get_dollar_pos(s);
	if (!i)
		return (ft_strdup(""));
	name = (char *)var_name(s, i + 1);
	if (!name)
		return (NULL);
	if (ft_is_digit(*name))
		return (check_name(name));
	value = (char *)var_value(envp, name);
	if (!value)
		return (free(name), free(value), ft_strdup(""));
	return (free(name), value);
}

/*
** Correct
** I may recompose (ft_recompose) right here, (before/after) removing quotes
*/
void	ft_expander(t_list **token, t_env envp)
{
	t_list	*tmp;

	tmp = *token;
	while (tmp)
	{
		expand_flag(tmp);
		if (tmp->exp_flag)
			tmp->expand = expand(envp, (char *)tmp->val);
		else
			tmp->expand = (char *)ft_rm_quotes(tmp);
			// tmp->expand = (char *)tmp->val;
		tmp = tmp->next;
	}
	// ft_recompose(token);
	// ft_quotes(token);
}
