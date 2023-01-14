/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:06:57 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/14 21:51:29 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	indexation(t_var *var, t_var *elem, int (*f)())
{
	int	index;

	index = 0;
	elem->id = 0;
	while (var)
	{
		if (f(var->name, elem->name) < 0)
			++index;
		var = var->next;
	}
	printf("index = %d\n", index);
	elem->id = index;
	return ;
}

t_var	*var_index(t_var **var)
{
	t_var	*tmp;

	tmp = *var;
	while (tmp)
	{
		indexation(*var, tmp, ft_strcmp);
		tmp = tmp->next;
	}
	return (*var);
}

/*
** Have the right index for each var->name
** Have to print env by sorting var->name
** A loop is necessary
*/
// void	sort_env(t_var *var)
// {
// }
