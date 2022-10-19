/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:05:11 by dsaada            #+#    #+#             */
/*   Updated: 2022/07/30 15:02:04 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../minishell.h"
# include "../parser/parser.h"

int	ft_cd(t_cmd *cmd, t_env *env);
int	ft_pwd(t_cmd *cmd, t_env *env);
int	ft_export(t_cmd *cmd, t_env *env);
int	ft_unset(t_cmd *cmd, t_env *env);
int	ft_env(t_cmd *cmd, t_env *env);
int	ft_exit(t_cmd_list *cmd_list, t_cmd *cmd, t_env *env);
int	ft_echo(t_cmd *cmd, t_env *env);

#endif
