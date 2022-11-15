/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:41:35 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/15 07:29:42 by ccouliba         ###   ########.fr       */
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
	if (cmd->param && *cmd->param)
	{
		tmp = cmd->param;
		syntax_error(*tmp, ERRNO_3, 2, ft_putstr_fd);
		return (127);
	}
	return (ft_print_env(var), EXIT_SUCCESS);
}
