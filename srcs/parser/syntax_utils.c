/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:04:56 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/15 06:56:24 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	syntax_error(char *token, char *err_syntax, int fd, void (*f)())
{
	f("minishell: ", fd);
	f(err_syntax, fd);
	f(" ", fd);
	f("`", fd);
	f(token, fd);
	f("'", fd);
	f("\n", fd);
	return ;
}

int	check_quotes_word(t_list *token)
{
	if (ft_check_quotes(token))
	{
		if (ft_open_quotes(token) || ft_strlen((char *)token->val) == 1)
		{
			syntax_error("quote", ERRNO_1, 2, ft_putstr_fd);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	wrong_next(t_list *token)
{
	if (token->type == PIPE || token->type == RD)
	{
		if (token->next->type == PIPE || token->next->type == RD)
		{
			syntax_error((char *)token->val, ERRNO_1, 2, ft_putstr_fd);
			return (EXIT_FAILURE);
		}
		if (token->next->type == VOID)
		{
			if (token->next->next->type == RD
				|| token->next->next->type == PIPE)
			{
				syntax_error((char *)token->val, ERRNO_1, 2, ft_putstr_fd);
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}

int	wrong_pipe(t_list *token)
{
	if (token->type == PIPE)
	{
		if (ft_strlen((char *)token->val) != 1)
		{
			syntax_error("pipeline", ERRNO_1, 2, ft_putstr_fd);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	wrong_rd(t_list *token)
{
	if (token->type == RD)
	{
		if (ft_strlen((char *)token->val) > 2)
		{
			syntax_error(token->val, ERRNO_1, 2, ft_putstr_fd);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
