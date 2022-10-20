/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:30:05 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/20 09:42:37 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_parser(t_list **token)
{
	t_list		*tmp;
	t_syntaxer	syntax;

	tmp = *token;
	init_syntaxer(syntax);
	if (ft_syntaxer(&tmp, syntax))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
