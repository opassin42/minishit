/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:38:26 by ccouliba          #+#    #+#             */
/*   Updated: 2022/07/12 01:48:56 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** TO DO : cd
** If path exists, just change dir to the path specified
** Else return to the previous dir
** Have to deal with PATH
*/
int ft_cd(char *path)
{
	int res;

	if (path)
		res = chdir(path);
	// else
	//     chdir
	if (!res)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
