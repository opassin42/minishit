/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 00:51:28 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/20 09:32:16 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
** How to properly define a cmd
** Maybe do it by another way (cf ft_builtin_cmd)
*/

int	init_function(t_func fct)
{
	fct[0] = is_heredoc;
	fct[1] = is_rd_in;
	fct[2] = is_rd_out;
	fct[3] = is_append;
	fct[4] = is_pipes;
	return (EXIT_SUCCESS);
}

static void	first_cmd(t_list **token)
{
	t_list	*tmp;

	tmp = *token;
	if (tmp)
	{
		if (tmp->type == WORD)
		{
			if (!tmp->next || (tmp->next && tmp->next->type == PIPE))
				tmp->fct = CMD;
		}
	}
	return ;
}

// static void	is_arg(t_list **token)
// {
// 	t_list	*tmp;

// 	tmp = *token;
// 	if (tmp->fct == CMD)
// 	{
// 		tmp = tmp->next;
// 		while (tmp)
// 		{
// 			if (tmp->type == WORD || tmp->type == VOID)
// 				tmp->fct = ARG;
// 			tmp = tmp->next;
// 		}
// 	}
// 	return ;
// }

static void	define_function(t_list *token, t_func fct)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (fct[i](token))
			token->fct = i;
		++i;
	}
}

void	ft_function(t_list **token, t_func fct)
{
	// int		i;
	t_list	*tmp;

	tmp = *token;
	first_cmd(&tmp);
	// printf("tmp->fct : [%d]\n", tmp->fct);
	tmp = tmp->next;
	while (tmp)
	{
		define_function(tmp, fct);
		tmp = tmp->next;
	}
}
