/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:17:05 by dsaada            #+#    #+#             */
/*   Updated: 2022/07/30 13:08:55 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"
#include "../../global.h"

int	check_export_valid(char *str)
{
	size_t	i;
	char	*name;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	if (i > 0)
	{
		name = ft_substr(str, 0, i);
		if (check_valid_identifier(name) == SUCCESS)
		{
			free(name);
			return (SUCCESS);
		}
		free(name);
	}
	return (FAILURE);
}

int	extract_name_value(char *str, char **name, char **value)
{
	int	i;
	int	start;

	i = 0;
	start = i;
	while (str[i] && str[i] != '=')
		i++;
	*name = ft_substr(str, start, i - start);
	if (!(*name))
		return (FAILURE);
	if (str[i] == '\0')
		*value = ft_strdup("");
	else
		*value = ft_substr(str, i + 1, ft_strlen(str) - i);
	if (!(*value))
	{
		free(*name);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	print_env_alpha(t_env *env)
{
	t_var	*current;
	t_var	*print;
	int		cpt;

	cpt = 0;
	while (cpt < env->size)
	{
		current = env->start;
		print = current;
		while (current != NULL)
		{
			if (current->print == 0 && sort_str(print->name, current->name) > 0)
				print = current;
			current = current->next;
			if (print->print == 1)
				print = current;
		}
		print->print = 1;
		printf("declare -x %s=\"%s\"\n", print->name, print->value);
		cpt++;
	}
	current = env->start;
	while (current != NULL)
	{
		current->print = 0;
		current = current->next;
	}
}

int	ft_export(t_cmd *cmd, t_env *env)
{
	int		i;
	char	*name;
	char	*value;

	i = 1;
	if (cmd->params[i] == NULL)
		print_env_alpha(env);
	while (cmd->params[i] != NULL)
	{
		if (check_export_valid(cmd->params[i]) == SUCCESS)
		{
			if (extract_name_value(cmd->params[i], &name, &value) == SUCCESS)
			{
				if (var_exist(env, name) == SUCCESS)
					unset_from_env(env, name);
				create_env_var(env, name, value);
			}
			g_status = EXIT_SUCCESS;
		}
		else
		{
			g_status = EXIT_FAILURE;
			write(2, "minishell: export: `", 20);
			write(2, cmd->params[i], ft_strlen(cmd->params[i]));
			write(2, "': not a valid identifier\n", 26);
		}
		i++;
	}
	return (SUCCESS);
}
