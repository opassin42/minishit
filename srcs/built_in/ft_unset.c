/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:42:36 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/17 18:52:16 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_check(t_cmd *cmd, t_env *envp)
{
	if (!cmd || !envp)
		return (0);
	return (get_nb_var(cmd));
}

/*
Type : Integer
Arg : list cmd
Role: calculate the nb of arg in parameter
Return value: nb of arg >> i (integer) 
*/
int	get_nb_var(t_cmd *cmd)
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

/*
Type : Void
Arg : t_var (structure of env's variable)
Role: free the env variable element passed in parameter
Return value: none 
*/
void	ft_free_var(t_var *var)
{
	if (var)
	{
		var->next = NULL;
		var = NULL;
	}
}

/*
Type : Void
Arg : [envp] -> pointer to the first environment's element
	  [var_name] -> variable name to delete (string) 
Role: delete the env variable whose the name has passed in parameter
Return value: none
*/
void	ft_delete_var(t_env *envp, char *var_name)
{
	t_var	*prev;
	t_var	*tmp;
	t_var	*var;

	if (!var_name)
		return ;
	var = envp->var;
	if (!ft_strcmp(var->name, var_name))
	{
		ft_free_var(var);
		return ;
	}
	while (var->next)
	{
		if (!ft_strcmp(var->next->name, var_name))
		{
			prev = var;
			tmp = var->next->next;
			prev->next = tmp;
			return ;
		}
		var = var->next;
	}
	return ;
}

/*
Type : Integer 
Arg : [envp] -> pointer to the first environment's element
[cmd] -> pointer to the first cmd's element 
Role: unset all the named variable passed in command line
Return value: this builtin always return 0 in case of success
*/
int	ft_unset(t_env *envp, t_cmd *cmd)
{
	int		nb_var;
	t_var	*var;

	nb_var = ft_check(cmd, envp);
	while (nb_var--)
	{
		if (envp->var)
		{
			var = envp->var;
			while (var && *cmd->param)
			{
				if (!ft_strcmp(var->name, *cmd->param))
				{
					ft_delete_var(envp, var->name);
					cmd->param++;
					break ;
				}
				var = var->next;
			}
			if (!var)
				cmd->param++;
		}
	}
	return (0);
}
