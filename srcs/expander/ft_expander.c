/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:45:01 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/13 17:23:55 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	*var_name(char *str, int start)
{
	int		i;
	char	*tmp;

	if (!str)
		return (NULL);
	i = start + 1;
	if (!str[i])
		return (NULL);
	tmp = NULL;
	while (str[i++])
	{
		if (ft_alnum_underscore(str[i]))
		{
			tmp = (void *)ft_substr(str, start, i - start);
			if (!tmp)
				return (NULL);
			return (tmp);
		}
	}
	return (NULL);
}

static char	*check_name(char *name)
{
	char	*tmp;

	if (!name)
		return (NULL);
	if (*(name + 1))
		tmp = name + 1;
	else
		tmp = ft_strdup("");
	return (tmp);
}

/*
** $_ -> last arg given to a cmd ! If no arg, print build_in PATH
** 
*/
char	*expand(t_env *envp, char *s)
{
	int		pos;
	char	*name;
	char	*var_val;

	if (!s)
		return (NULL);
	pos = ft_get_dollar_pos(s);
	name = (char *)var_name(s, pos);
	if (!name)
		return (NULL);
	name = check_name(name);
	if (!name)
		return (NULL);
	if (!ft_strcmp(name, "?"))
		var_val = ft_itoa(g_data.status);
	else
		var_val = find_value(envp, name);
	if (!var_val)
		return (ft_strdup(""));
	negative_hashing(var_val, ' ');
	return (var_val);
}

static void	if_exp_flag(t_env *envp, t_list *tmp, char *first_val, char *(*f)())
{
	char	*exp_val;

	exp_val = f(envp, first_val);
	if (exp_val)
		tmp->expand = exp_val;
	return ;
}

void	ft_expander(t_list **token, t_env *envp)
{
	char	*first_val;
	t_list	*tmp;

	tmp = *token;
	while (tmp)
	{
		expand_quote_flag(tmp);
		first_val = (char *)tmp->val;
		if (tmp->quote)
		{
			first_val = remove_quotes(tmp);
			if (!first_val)
				return ;
		}
		if (tmp->exp_flag)
			if_exp_flag(envp, tmp, first_val, ft_recompose);
		else
			tmp->expand = first_val;
		tmp = tmp->next;
	}
}
