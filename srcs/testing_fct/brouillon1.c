/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brouillon1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 03:29:31 by ccouliba          #+#    #+#             */
/*   Updated: 2022/08/30 18:07:00 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** How can i change a node containing quotes
** To string with or without appropriate quotes ????
*/

/*
** Get the address of the first quote (opening quotes)
*/
// static int	start_quotes(char *s, int (*f)(int))
// {
// 	int	i;

// 	i = 0;
// 	while (s[i] && f(s[i]))
// 		++i;
// 	return (i);
// }

// static int	between_quotes(char *s, int index, int (*f)(int))
// {
// 	while (s[index] && !f(s[index]))
// 		++index;
// 	return (index);
// }

// static void	*ft_fill(char *s, int (*f)(int))
// {
// 	int		index;
// 	void	*tmp;
// 	void	*quote;

// 	index = start_quotes(s, f);
// 	tmp = ft_substr(s, 0, index);
// 	printf("tmp1 : [%s]\n", (char *)tmp);
// 	quote = tmp;
// 	printf("quote1 : [%s]\n", (char *)quote);
// 	tmp = NULL;
// 	tmp = ft_substr(s, index, between_quotes(s, index, f));
// 	printf("tmp2 : [%s]\n", (char *)tmp);
// 	quote = ft_strjoin(quote, tmp);
// 	printf("quote2 : [%s]\n", (char *)quote);
// 	return (quote);
// }

// void	*ft_quotes(char *s)
// {
// 	void	*quote;

// 	quote = NULL;
// 	if (*s == '\'')
// 		quote = ft_fill(s, ft_flag_s_quote);
// 	else if (*s == '"')
// 		quote = ft_fill(s, ft_flag_d_quote);
// 	return (quote);
// }

/*
	tmp = NULL;
	index = between_quotes(s, index + 1) + 1;
	tmp = ft_substr(s, index, close_quotes(s, index) + 1);
	printf("tmp3 : [%s]\n", (char *)tmp);
	quote = ft_strjoin(quote, tmp);
	printf("quote3 : [%s]\n", (char *)quote);
*/