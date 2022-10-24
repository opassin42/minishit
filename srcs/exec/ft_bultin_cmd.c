/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bultin_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:31:33 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/24 01:33:17 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	count_arg_nb(t_list *token)
// {
// 	int	i;

// 	i = 0;
// 	token = token->next;
// 	while (token)
// 	{
// 		if (token->type != WORD && token->type != VOID)
// 			break ;
// 		++i;
// 		token = token->next;
// 	}
// 	return (i);
// }

// char	**malloc_arg(t_list *token)
// {
// 	int		arg_nb;
// 	char	**param;

// 	arg_nb = count_arg_nb(token);
// 	if (!arg_nb)
// 		return (NULL);
// 	printf ("arg_nb = %d\n", arg_nb);
// 	param = malloc(sizeof(char *) * (arg_nb + 1));
// 	if (!param)
// 		return (NULL);
// 	token = token->next;
// 	if (token->type == VOID)
// 		token = token->next;
// 	param = (char **)fill_arg(token, param, arg_nb);
// 	if (!param)
// 		return (NULL);
// 	return (param);
// }
