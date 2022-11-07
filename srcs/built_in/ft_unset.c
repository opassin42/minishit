/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:42:36 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/05 04:42:38 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int		get_nb_var(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->param)
	{
		while (cmd->param[i])
			i++;
	}
	return (i);
}

void	ft_free_var(t_var *var)
{
	free(var->name);
	free(var->value);
	var->next = NULL;
	var = NULL;
}

void	ft_delete_var(t_env *envp, char *var_name)
{
	t_var	*prev;
	t_var	*tmp;
	t_var	*var;

	var = envp->var;
	if (!ft_strcmp(var->name, var_name))
	{
		envp->var = envp->var->next;
		ft_free_var(var);
		return ;
	}
	while (var->next)
	{
		if (!ft_strcmp(var->next->name, var_name))
		{
			prev = var;
			tmp = var->next->next;
			ft_free_var(var->next);
			prev->next = tmp;
			return ;
		}
		var = var->next;
	}
	return ;
}

int	ft_unset(t_env *envp, t_cmd *cmd)
{
	t_var	*var;
	int		nb_var;

	if (cmd)
		nb_var = get_nb_var(cmd);
	while(nb_var--)
	{
		if (envp->var)
			var = envp->var;
		else
			return (0);
		while(var->name != NULL && *cmd->param != NULL)
		{
			if (!ft_strcmp(var->name, *cmd->param))
			{
				ft_delete_var(envp, var->name);
				cmd->param++;
				break;
			}
			var = var->next;
		}
	}
	return (0);
}