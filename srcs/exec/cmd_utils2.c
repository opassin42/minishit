/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 02:32:23 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/26 01:44:57 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_malloc_double_p(t_list *token)
{
	int		i;
	char	**param;

	if (!token)
		return ((char **) NULL);
	i = ft_lstsize(token);
	param = (char **)push_top(&start, (sizeof(char *) * (i + 1)));
	if (!param)
		return (gc_free(), NULL);
	i = 0;
	while (token)
	{
		param[i] = ft_strdup(token->val);
		if (!param[i])
			return (gc_free(), (char **) NULL);
		token = token->next;
		++i;
	}
	param[i] = 0;
	return (param);
}
