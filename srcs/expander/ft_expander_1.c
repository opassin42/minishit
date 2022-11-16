/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:45:01 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/15 17:34:46 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static void	expand_flag(t_list *token)
{
	char	*s;

	s = (char *)token->val;
	// token->exp_flag = 0;
	if (ft_strchr(s, '$') && *(s + 1))
	{
		if (!check_simple_quotes(s))
			token->exp_flag = 1;
	}
	return ;
}

static char	*remove_quotes(t_list *token)
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
		expand_flag(tmp);
		first_val = remove_quotes(tmp);
		if (!first_val)
			return ;
		if (tmp->exp_flag)
		{
			exp_val = ft_recompose(envp, first_val);
			if (exp_val)
				tmp->expand = exp_val;
			else
				return ;
		}
		else
			tmp->expand = first_val;
		tmp = tmp->next;
	}
}
