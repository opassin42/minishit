/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:29:39 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/17 18:12:03 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	word_type(void *p)
{
	char	*tmp;

	tmp = (char *)p;
	while (*tmp)
	{
		if (ft_strchr(DELIM, *tmp))
			return (EXIT_FAILURE);
		++tmp;
	}
	return (EXIT_SUCCESS);
}

int	pipe_type(void *p)
{
	char	*tmp;

	tmp = (char *)p;
	while (*tmp)
	{
		if (*tmp != '|')
			return (EXIT_FAILURE);
		++tmp;
	}
	return (EXIT_SUCCESS);
}

int	rd_type(void *p)
{
	char	*tmp;

	tmp = (char *)p;
	while (*tmp)
	{
		if (*tmp != '<' && *tmp != '>')
			return (EXIT_FAILURE);
		++tmp;
	}
	return (EXIT_SUCCESS);
}

void	ft_type(t_list **token)
{
	t_list	*tmp;

	tmp = *token;
	while (tmp)
	{
		tmp->type = -1;
		if (!ft_not_only_space(tmp->val))
			tmp->type = VOID;
		else if (!word_type(tmp->val))
			tmp->type = WORD;
		else if (!pipe_type(tmp->val))
			tmp->type = PIPE;
		else if (!rd_type(tmp->val))
			tmp->type = RD;
		tmp = tmp->next;
	}
}
