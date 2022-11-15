/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 04:45:05 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/15 17:33:52 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_status;

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
