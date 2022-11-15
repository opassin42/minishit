/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 03:28:46 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/15 17:42:13 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_var_name(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '=')
			break ;
	}
	return (ft_substr(s, 0, i));
}

t_var	*ft_new_var(t_list *token)
{
	int		end;
	int		begin;
	char	*str;
	t_var	*var;

	str = (char *)token->val;
	var = (t_var*)push_top(&start, sizeof(t_var));
	if (!var)
	{
		gc_free();
		return (NULL);
	}
	var->name = ft_var_name(str);
	begin = ft_strlen(var->name) + 1;
	end = ft_strlen(str) - 1;
	var->value = ft_substr(str, begin, end);
	var->next = NULL;
	return (var);
}

t_var	*ft_last_var(t_var *var)
{
	if (var)
	{
		while (var->next)
			var = var->next;
	}
	return (var);
}

void	ft_var_addback(t_var **var, t_var *new_var)
{
	if (new_var)
	{
		if (*var)
			ft_last_var(*var)->next = new_var;
		else
			*var = new_var;
	}
}

int	ft_size_of_env(t_var *var)
{
	int	i;

	i = 0;
	if (var)
	{
		i = 0;
		while (var)
		{
			var = var->next;
			++i;
		}
	}
	return (i);
}
