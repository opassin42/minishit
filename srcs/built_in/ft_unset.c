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
	free(var->name);
	free(var->value);
	var->next = NULL;
	var = NULL;
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

/*
Type : Integer
Arg : [envp] -> pointer to the first environment's element (struct t_env, cf: structs.h)
	  [cmd] -> pointer to the first cmd's element which is the arguments of the cmd (struct t_cmd, cf: structs.h)
Role: unset all the named variable passed in command line
Return value: this builtin always return 0 in case of success
*/
int	ft_unset(t_env *envp, t_cmd *cmd)
{
	t_var	*var;
	int		nb_var;

	if (cmd)
		nb_var = get_nb_var(cmd);
	while (nb_var--)
	{
		if (envp->var)
			var = envp->var;
		else
			return (0);
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
	return (0);
}
