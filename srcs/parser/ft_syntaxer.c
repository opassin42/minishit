/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntaxer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 00:51:18 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/15 17:15:52 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_check_last_token(t_list *token)
{
	t_list	*last;

	last = ft_lstlast(token);
	if (last->type == PIPE || last->type == RD)
	{
		if (last->type == PIPE)
			syntax_error((char *)last->val, ERRNO_1, 2, ft_putstr_fd);
		else
			syntax_error("newline", ERRNO_1, 2, ft_putstr_fd);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_check_first_token(t_list *token)
{
	char	*s;

	s = token->val;
	if (token->type == PIPE || !ft_strcmp(s, "<"))
	{
		if (token->type == PIPE)
		{
			syntax_error((char *)token->val, ERRNO_1, 2, ft_putstr_fd);
			return (EXIT_FAILURE);
		}
		else if (!ft_strcmp(s, "<"))
		{
			ft_putstr_fd("minishell: no such file or directory\n", 2);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

static int	check_syntax(t_list *token, t_syntaxer synt)
{
	int	i;
	int	ret;

	i = 0;
	while (i < 4)
	{
		ret = synt[i](token);
		if (ret)
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}

int	ft_syntaxer(t_list **token, t_syntaxer synt)
{
	t_list	*tmp;

	tmp = (t_list *)(*token);
	if (ft_check_last_token(tmp) || ft_check_first_token(tmp))
		return (EXIT_FAILURE);
	while (tmp)
	{
		if (check_syntax(tmp, synt))
			return (EXIT_FAILURE);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
