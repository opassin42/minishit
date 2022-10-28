/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 04:45:05 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/27 22:29:59 by ccouliba         ###   ########.fr       */
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
	while (s[i])
	{
		if (s[i] == '$')
			break ;
		++i;
	}
	return (i);
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
	return (NULL);
}
