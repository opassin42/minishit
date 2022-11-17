/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opassin <ccouliba@student.42.fr>  	        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:38:26 by opassin           #+#    #+#             */
/*   Updated: 2022/07/12 01:48:56 by opassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * ft_no_home 	: print the home's path error 
 * Type 		: integer
 * Parameter	: struct upvarenv
 * Return value: 1 in case of fail
 */
int	ft_no_home(t_upvarenv *upvarenv)
{
	free(upvarenv);
	printf("minishell: cd: HOME not set\n");
	return (1);
}

/*
 * is_alphanum 	: check if the character is alphanum
 * Type 		: integer
 * Parameter	: struct upvarenv
 * Return value: 1 in case of success or 0 in case of fail
 */
int	is_alphanum(t_upvarenv *upvarenv)
{
	if ((upvarenv->path[0] >= 48 && upvarenv->path[0] <= 57)
		|| (upvarenv->path[0] >= 65 && upvarenv->path[0] <= 90)
		|| (upvarenv->path[0] >= 97 && upvarenv->path[0] <= 122)
		|| (upvarenv->path[0] == 126 && upvarenv->path[1] == 47))
		return (1);
	return (0);
}
