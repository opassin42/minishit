/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:45:01 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/27 22:32:11 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	expand_flag(t_list *token)
{
	char	*s;

	s = (char *)token->val;
	if (ft_strchr(s, '$') && *(s + 1))
	{
		if (check_simple_quotes(s))
			token->exp_flag = 0;
		else
			token->exp_flag = 1;
	}
	else
		token->exp_flag = 0;
	return ;
}

// void	*var_value(t_env envp, char *name)
// {
// 	char	*tmp;

// 	if (!name)
// 		return (NULL);
// 	tmp = find_value(&envp, name);
// 	if (!tmp)
// 		return (ft_strdup(""));
// 	return (tmp);
// }

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

static char	*expand(t_env envp, t_list *token)
{
	int		pos;
	char	*tmp;
	char	*name;
	char	*var_val;

	tmp = (char *)token->val;
	pos = ft_get_dollar_pos(tmp);
	name = var_name(tmp, pos);
	name = check_name(name);
	if (!name)
		return (ft_strdup(""));
	printf("-> name : [%s]\n", name);
	var_val = find_value(&envp, name);
	if (!var_val)
		return (ft_strdup(""));
	printf("-> val : [%s]\n", var_val);
	return (var_val);
}

/*
** Correct
** I may recompose (ft_recompose) right here, (after)removing quotes
**
** Have this error : "Permission denied"
** By execve() for this input : $aaaaaa
**
** Handle this input : $1a
*/
void	ft_expander(t_list **token, t_env envp)
{
	t_list	*tmp;

	tmp = *token;
	while (tmp)
	{
		expand_flag(tmp);
		if (tmp->exp_flag)
			tmp->expand = expand(envp, tmp);
		else
			tmp->expand = (char *)tmp->val;
		// if (!tmp->expand || !*(tmp->expand))
		// 	tmp->expand = ft_strdup("");
		tmp = tmp->next;
	}
	ft_quotes(token);
	// ft_recompose(token);
}
