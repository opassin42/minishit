/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:41:35 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/24 05:30:54 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_print_env(t_var *var)
{
	while (var)
	{
		printf("%s\e[0;33m=\e[0m%s\n", var->name, var->value);
		var = var->next;
	}
}

int	ft_env(t_env *envp, t_cmd *cmd)
{
	char	**tmp;
	t_var	*var;

	var = envp->var;
	if (!var)
		return (EXIT_FAILURE);
	if (!cmd->arg)
		return (ft_print_env(var), (EXIT_SUCCESS));
	else
		tmp = cmd->arg;
	printf ("minishell: env: '%s': No such file or directory\n", *tmp);
	return (EXIT_FAILURE);
}
