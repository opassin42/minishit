/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:29:39 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/13 08:32:49 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_word_type(void *p)
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

static int	ft_pipe_type(void *p)
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

static int	ft_rd_type(void *p)
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
		if (!ft_not_only_space(tmp->val))
			tmp->type = SPACE;
		else if (!ft_word_type(tmp->val))
			tmp->type = WORD;
		else if (!ft_pipe_type(tmp->val))
			tmp->type = PIPE;
		else if (!ft_rd_type(tmp->val))
			tmp->type = RD;
		tmp = tmp->next;
	}
}
