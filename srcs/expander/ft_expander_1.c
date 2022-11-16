/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:45:01 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/16 06:21:05 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*var_name(char *str, int start)
{
	int		i;
	char	*tmp;

	if (!str)
		return (NULL);
	i = start + 1;
	if (!str[i])
		return (NULL);
	tmp = NULL;
	if (!str[i + 1])
		tmp = ft_strdup(&str[i]);
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
	else if (!*(name + 1))
		tmp = ft_strdup("");
	return (tmp);
}

char	*find_value(t_env *envp, char *var_name)
{
	t_var	*var;

	var = envp->var;
	if (!var_name || (*var_name == '$' && !(*var_name + 1)))
		return (NULL);
	while (var)
	{
		if (!ft_strcmp(var->name, var_name))
			return (var->value);
		var = var->next;
	}
	return (ft_strdup(""));
}

char	*expand(t_env envp, char *s)
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
		var_val = ft_itoa(g_status);
	else
		var_val = find_value(&envp, name);
	if (!var_val)
		return (ft_strdup(""));
	return (var_val);
}

/*
** Correct
** I may recompose (ft_recompose) right here, (after)removing quotes
** Handle this input : $1abc
** warning : if export a="o hi" -> ech$a = hi
*/
void	ft_expander(t_list **token, t_env envp)
{
	char	*exp_val;
	char	*first_val;
	t_list	*tmp;

	tmp = *token;
	exp_val = NULL;
	while (tmp)
	{
		expand_quote_flag(tmp);
		first_val = remove_quotes(tmp);
		if (!first_val)
			return ;
		if (tmp->exp_flag)
		{
			exp_val = ft_assemble(envp, tmp, first_val);
			if (exp_val)
				tmp->expand = exp_val;
		}
		else
			tmp->expand = first_val;
		tmp = tmp->next;
	}
}
