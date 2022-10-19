/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:41:35 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/09 17:52:50 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_env_option(t_list *token)
{
	if (!ft_strcmp(token->val, "env") && token->next)
		if (token->next->type == WORD)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	ft_print_env(t_var *var)
{
	while (var)
	{
		printf("%s\e[0;33m=\e[0m%s\n", var->name, var->value);
		var = var->next;
	}
}

int	ft_env(t_env *envp, t_list *token)
{
	t_var	*var;

	var = envp->var;
	if (!var)
		return (EXIT_FAILURE);
	if (check_env_option(token))
	{
		printf ("minishell: env: '%s': No such file or directory\n",
			(char *)token->next->val);
		return (EXIT_FAILURE);
	}
	ft_print_env(var);
	return (EXIT_SUCCESS);
}
