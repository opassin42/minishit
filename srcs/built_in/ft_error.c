/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 02:48:40 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/15 17:39:42 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export_error(char *s)
{
	char	**tmp;

	if (!s)
		return ;
	if (*s == '-')
	{
		tmp = ft_split(s, '=');
		if (!tmp)
			return ;
		printf("minishell: export: '%s': bad option\n", *tmp);
		return ;
	}
	printf("minishell: export: '%s': not a valid identifier\n", s);
	return ;
}
