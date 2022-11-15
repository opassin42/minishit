/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <dsaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:48:32 by dsaada            #+#    #+#             */
/*   Updated: 2022/07/30 13:00:38 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "../../minishell.h"

typedef struct s_var
{
	char			*name;
	char			*value;
	int				print;
	struct s_var	*prev;
	struct s_var	*next;
}	t_var;

typedef struct s_env
{
	int		size;
	t_var	*start;
	t_var	*end;
}	t_env;

//env
int		parse_env(t_env *env, char **envp);
char	*get_env_var(t_env *env, char *name);
int		create_env_var(t_env *env, char *name, char *value);
void	print_env(t_env *env);
char	**generate_envp(t_env *env);
//env_utils.c
int		var_exist(t_env *env, char *str);
t_var	*init_var(char *name, char *value);
void	init_env(t_env *env);
void	add_var(t_env *env, t_var *var);
//env_utils_free.c
int		delete_var(t_env *env, t_var *var);
int		free_env(t_env *env);
void	unset_from_env(t_env *env, char *str);

#endif
