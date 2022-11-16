/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:41:35 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/25 04:25:30 by ccouliba         ###   ########.fr       */
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

void	ft_swap(t_var *a, t_var *b)
{
	t_var	*tmp;

	tmp = a;
	a = b;
	b = tmp;
}

void	ft_export_env(t_var *var)
{
	int swapped;
	t_var	*var_env;
	t_var	*current;
	char 	*tmp; 
	char 	*tmp2;

	var_env = NULL;
	swapped = 1;
	while (swapped)
    {
        swapped = 0;
        current = var;

        while (current->next != var_env)
        {
            tmp = strdup(current->name);
            tmp2 = strdup(current->next->name);
            if (ft_strcmp(tmp, tmp2) > 0)
            {
                ft_swap(current, current->next);
                swapped = 1;
            }
            current = current->next;
        }
        var_env = current;
     }
	while (var_env)
	{
		printf("declare -x %s\e[0;33m=\e[0m%s\n", var_env->name, var_env->value);
		var_env = var_env->next;
	}
}

int	ft_env(t_env *envp, t_cmd *cmd)
{
	char	**tmp;
	t_var	*var;

	var = envp->var;
	if (!var)
		return (EXIT_FAILURE);
	if (!cmd->param)
		return (ft_print_env(var), (EXIT_SUCCESS));
	else
		tmp = cmd->param;
	printf ("minishell: env: '%s': No such file or directory\n", *tmp);
	return (EXIT_FAILURE);
}
