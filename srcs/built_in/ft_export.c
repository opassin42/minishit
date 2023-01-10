/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:39:55 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/07 21:05:08 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_name(char *name)
{
	int		n;

	n = ft_strlen(name);
	if (name[0] == '_' || ft_isalnum(name[0]))
	{
		if ((name[n - 1] >= 48 && name[n - 1] <= 57) || ft_isalnum(name[n - 1]))
			return (1);
	}
	return (0);
}

char	*split_name(t_cmd *cmd, int i)
{
	char	*str;
	char	*str2;
	size_t	name_size;

	if (!cmd->param)
		return (NULL);
	str = cmd->param[i];
	str2 = ft_strchr(str, '=');
	if (!str2)
		return (str);
	name_size = str2 - str;
	return (ft_substr(str, 0, name_size));
}

char	*split_value(t_cmd *cmd, int i)
{
	char	*str;
	size_t	value_size;

	if (!cmd->param[i])
		return (NULL);
	str = ft_strchr(cmd->param[i], '=');
	if (str == NULL)
		return (cmd->param[i]);
	value_size = (str + ft_strlen(cmd->param[i])) - str;
	return (ft_substr(str + 1, 0, value_size));
}

t_var	*ft_new_var_env(t_cmd *cmd, int i)
{
	t_var	*var;

	var = (t_var *)push_top(&g_data.gc, sizeof(t_var));
	if (!var)
		return (gc_free(), NULL);
	var->name = split_name(cmd, i);
	if (!var->name)
		return (NULL);
	if (is_valid_name(var->name) == 0)
		return (NULL);
	if (!ft_strcmp(var->name, cmd->param[i]))
		++i;
	var->value = split_value(cmd, i);
	if (!var->value)
		return (NULL);
	var->next = NULL;
	return (var);
}

// void	change_var_value(t_env *envp, t_cmd *cmd, int i)
// {
// 	t_var	*var;
// 	char	*name;

// 	if (!envp)
// 		return ;
// 	var = envp->var;
// 	if (!s)
// 		return ;
// 	name = split_name(cmd, i);
// 	if (!name)
// 		return ;
// 	while (var)
// 	{
// 		if (!ft_strcmp(var->name, name))
// 		{
// 			var->value = split_value(cmd, i);
// 			if (!var->value)
// 				return ;
// 		}
// 		var = var->next;
// 	}
// }

int	ft_export(t_env *envp, t_cmd *cmd)
{
	t_var	*var;
	int		nb_var;
	int		i;

	i = 0;
	var = NULL;
	nb_var = 0;
	if (!envp)
		return (printf("%s\n", MISSING_ENV));
	if (cmd)
		nb_var = get_nb_var(cmd);
	if (!cmd->param)
		return (ft_export_env(envp->var), 0);
	if (envp)
	{
		if (envp->var)
			var = envp->var;
	}
	while (i < nb_var)
	{
		ft_var_addback(&var, ft_new_var_env(cmd, i++));
	}
	return (0);
}
