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


int		get_nb_var(t_env * envp, t_cmd *new_cmd)
{
	int	i;

	i = 0;
	while (cmd[i]->param)
		i++;
	return (i;)
}

int	ft_unset(t_env *envp, t_cmd *cmd, int i)
{
	char	*var;
	char	*var_cmd;
	char	*tmp;

	tmp = NULL;
	var = envp->var;
	while(i--)
	{
		while(var->name)
		{
			if (ft_strcmp(var->name, *cmd->param))
			{
				ft_delete_var("var->name");
				cmd->param++;
				break;
			}
			var = var->next;
		}
	}
	
}