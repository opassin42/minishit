/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:40:17 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/07 01:19:52 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** cd utils
*/
int	ft_no_home(t_upvarenv *upvarenv)
{
	// free(upvarenv);
	ft_putstr_fd("minishell: cd: HOME not set\n", 1);
	return (1);
}

int	is_alphanum(t_upvarenv *upvarenv)
{
	if ((upvarenv->path[0] >= 65 && upvarenv->path[0] <= 90)
		|| (upvarenv->path[0] >= 97 && upvarenv->path[0] <= 122)
		|| (upvarenv->path[0] == 126 && upvarenv->path[1] == 47))
		return (1);
	return (0);
}
