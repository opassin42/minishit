/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <dsaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:49:29 by dsaada            #+#    #+#             */
/*   Updated: 2022/07/30 13:01:48 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../pwd/pwd.h"
#include "../builtins.h"
#include "../../global.h"

char	**generate_envp(t_env *env)
{
	char	**envp;
	int		i;
	t_var	*var;

	envp = malloc(sizeof(char *) * (env->size + 1));
	if (!envp)
		return (NULL);
	envp[env->size] = NULL;
	var = env->start;
	i = 0;
	while (var != NULL)
	{
		envp[i] = ft_strcat_sep(var->name, var->value, '=');
		if (!envp[i])
		{
			free_tab(envp);
			return (NULL);
		}
		i++;
		var = var->next;
	}
	return (envp);
}

int	ft_env(t_cmd *cmd, t_env *env)
{
	t_var	*var;

	(void)cmd;
	var = env->start;
	while (var != NULL)
	{
		printf("%s=%s\n", var->name, var->value);
		var = var->next;
	}
	g_status = EXIT_SUCCESS;
	return (SUCCESS);
}

char	*get_env_var(t_env *env, char *name)
{
	t_var	*current;

	if (!env)
		return (ft_strdup(""));
	current = env->start;
	while (current != NULL)
	{
		if (ft_strcmp(name, current->name) == SUCCESS)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (ft_strdup(""));
}

int	create_env_var(t_env *env, char *name, char *value)
{
	t_var	*var;

	var = init_var(name, value);
	if (!var)
		return (FAILURE);
	add_var(env, var);
	return (SUCCESS);
}

static int	parse_env_var(t_env *env, char *str)
{
	size_t	i;
	size_t	start;
	char	*name;
	char	*value;

	i = 0;
	start = i;
	while (str[i] && str[i] != '=')
		i++;
	name = ft_substr(str, start, i - start);
	if (!name)
		return (FAILURE);
	value = ft_substr(str, i + 1, ft_strlen(str) - i);
	if (!value)
	{
		free(name);
		return (FAILURE);
	}
	if (create_env_var(env, name, value) != SUCCESS)
	{
		free(name);
		free(value);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	ft_atoi_shlvl(char *str, int *errflag)
{
	int	i;
	int	j;
	int	sign;
	int	res;

	res = 0;
	i = 0;
	sign = 1;
	while (str[i] != '\0' && is_wspace(str[i]) == SUCCESS)
		i++;
	j = 0;
	if (str[i + j] != '\0' && str[i + j] == '-')
	{
		sign = -1;
		j++;
	}
	else if (str[i + j] != '\0' && str[i + j] == '+')
		j++;
	while (str[i + j] != '\0')
	{
		if (str[i + j] <= '9' && str[i + j] >= '0')
		{
			res = res * 10 + str[i + j] - '0';
			j++;
		}
		else
		{
			while (str[i + j] != '\0')
			{
				if (is_tabspace(str[i + j]) == FAILURE)
					*errflag = FAILURE;
				i++;
			}
			return (res);
		}
	}
	return (res * sign);
}

int	ft_handle_shlvl(t_env *env)
{
	char	*name;
	char	*value;
	int		res;
	int		errflag;

	if (var_exist(env, "SHLVL") == FAILURE)
	{
		name = ft_strdup("SHLVL");
		if (!name)
			return (FAILURE);
		value = ft_strdup("1");
		if (!value)
		{
			free(name);
			return (FAILURE);
		}
		if (create_env_var(env, name, value) != SUCCESS)
			return (FAILURE);
	}
	else
	{
		value = get_env_var(env, "SHLVL");
		if (!value)
			return (FAILURE);
		errflag = 0;
		res = ft_atoi_shlvl(value, &errflag);
		if (errflag == FAILURE)
			res = 1;
		else if (res < 0)
			res = 0;
		else
		{
			res += 1;
			if (res > 998)
			{
				free(value);
				value = int_to_str(res);
				if (!value)
					return (FAILURE);
				write(2, "minishell: warning: shell level (", 33);
				write(2, value, ft_strlen(value));
				write(2, ") too high, resetting to 1\n", 27);
				res = 1;
			}
		}
		free(value);
		value = int_to_str(res);
		if (!value)
			return (FAILURE);
		name = ft_strdup("SHLVL");
		if (!name)
		{
			free(value);
			return (FAILURE);
		}
		unset_from_env(env, name);
		if (create_env_var(env, name, value) != SUCCESS)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	ft_handle_pwd(t_env *env)
{
	char	*name;
	char	*value;

	if (var_exist(env, "PWD") == FAILURE)
	{
		name = ft_strdup("PWD");
		if (!name)
			return (FAILURE);
		value = get_cwd();
		if (!value)
		{
			free(name);
			return (FAILURE);
		}
		if (create_env_var(env, name, value) != SUCCESS)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	parse_env(t_env *env, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (parse_env_var(env, envp[i]) == FAILURE)
			return (FAILURE);
		i++;
	}
	if (ft_handle_shlvl(env) == FAILURE)
		return (FAILURE);
	if (ft_handle_pwd(env) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
