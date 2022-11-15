/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:39:55 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/15 17:39:57 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*int		is_valid_name(char *str)
{

}*/

char	*split_name(t_cmd *cmd, int i)
{
	char	*str;
	int		name_size;

	str = cmd->param[i];
	name_size = ft_strchr(str, '=') - str;
	return (ft_substr(str, 0, name_size));
}

char	*split_value(t_cmd *cmd, int i)
{
	char	*str;
	int		value_size;

	str = ft_strchr(cmd->param[i], '=');
	value_size = (str + ft_strlen(cmd->param[i])) - str;
	return (ft_substr(str, 0, value_size));
}

t_var	*ft_new_var_env(t_cmd *cmd, int i)
{
	t_var *var;

	var = push_top(&start, sizeof(t_var));
	if (!var)
	{
		gc_free();
		return (NULL);
	}
	var->name = split_name(cmd, i);
	var->value = split_value(cmd, i);
	var->next = NULL;
	return (var);
}

int	ft_export(t_env *envp, t_cmd *cmd)
{
	t_var	*var;
	int		nb_var;
	int		i;

	i = 0;
	if (cmd)
		nb_var = get_nb_var(cmd);
	if(!cmd->param)
		ft_export_env(envp->var);
	if (envp->var)
		var = envp->var;
	while (var)
		var = var->next;
	while (i++ < nb_var)
	{
		var = ft_new_var_env(cmd, i);
		var = var->next;		
	}
	return (0);
}
