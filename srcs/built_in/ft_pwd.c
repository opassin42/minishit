/* ************************************************************************** */
/*	                                                                          */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:38:29 by ccouliba          #+#    #+#             */
/*   Updated: 2022/07/12 01:18:01 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Print the absolute path of the current working directory
*/

int	ft_pwd(void)
{
	char			*buf;
	char			*path;
	unsigned long	size;

	buf = malloc(sizeof(char) * BUFFER_SIZE);
	if (!buf)
		return (EXIT_FAILURE);
	size = sizeof(char) * BUFFER_SIZE;
	path = getcwd(buf, size);
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	return (free(buf), EXIT_SUCCESS);
}
