/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:21:28 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/20 01:52:13 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cmd_error(char *token, char *err_msg, int fd, void (*f)())
{
	f("minishell: ", fd);
	f(token, fd);
	f(": ", fd);
	f(err_msg, fd);
	f("\n", fd);
	exit(g_data.status);
}

int	check_cmd(char *s)
{
	int		flag;
	char	*tmp;

	flag = 0;
	tmp = s;
	if (*s == '.' && ft_strlen(s) == 1)
		return (g_data.status = 2, EXIT_FAILURE);
	while (*s)
	{
		if (*s != '.' && *s != '/')
		{
			flag = 1;
			break ;
		}
		++s;
	}
	if (!flag)
	{
		if (ft_strchr(tmp, '/'))
			return (g_data.status = 126, EXIT_FAILURE);
		return (g_data.status = 127, EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
