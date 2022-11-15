/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <dsaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:47:36 by dsaada            #+#    #+#             */
/*   Updated: 2022/07/30 13:09:55 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"
#include "../../global.h"

void	pwd(void)
{
	char	buff[1024];

	getcwd(buff, sizeof(buff));
	printf("%s\n", buff);
}

char	*get_cwd(void)
{
	char	buff[1024];
	int		i;
	char	*res;

	getcwd(buff, sizeof(buff));
	res = malloc(sizeof(char) * (ft_strlen(buff) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (buff[i] != '\0')
	{
		res[i] = buff[i];
		i++;
	}
	res[i] = '\0';
	return (res);	
}

int		ft_pwd(t_cmd *cmd, t_env *env)
{
	(void)cmd;
	(void)env;
	pwd();
	g_status = EXIT_SUCCESS;
	return (SUCCESS);
}
