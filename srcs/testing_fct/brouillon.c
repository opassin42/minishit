/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brouillon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 03:28:31 by ccouliba          #+#    #+#             */
/*   Updated: 2022/08/11 03:28:52 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_dquote(void *p)
{
	char	*tmp;

	tmp = (char *)p;
	while (*tmp)
	{
		if (*tmp != '"')
			return (EXIT_FAILURE);
		++tmp;
	}
	return (EXIT_SUCCESS);
}

int	ft_is_pipe(void *p)
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

int	ft_is_quote(void *p)
{
	char	*tmp;

	tmp = (char *)p;
	while (*tmp)
	{
		if (*tmp != '\'')
			return (EXIT_FAILURE);
		++tmp;
	}
	return (EXIT_SUCCESS);
}

int	ft_is_rd_in(void *p)
{
	char	*tmp;

	tmp = (char *)p;
	while (*tmp)
	{
		if (*tmp != '<')
			return (EXIT_FAILURE);
		++tmp;
	}
	return (EXIT_SUCCESS);
}

int	ft_is_rd_out(void *p)
{
	char	*tmp;

	tmp = (char *)p;
	while (*tmp)
	{
		if (*tmp != '>')
			return (EXIT_FAILURE);
		++tmp;
	}
	return (EXIT_SUCCESS);
}
