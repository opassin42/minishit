/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recompose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 08:11:34 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/18 22:41:24 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Does not join like i want
*/

static int	check_for_joining(t_list *curr, t_list *next)
{
	if (curr->type == WORD)
		if (curr->type == next->type)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	*non_word_token(t_list *token)
{
	while (token)
	{
		if (token->type != WORD)
			return ((void *)token);
		token = token->next;
	}
	return (NULL);
}

static char	*join_word_type(t_list **token)
{
	char	*new_val;
	t_list	*tmp;
	t_list	*curr;

	tmp = *token;
	curr = (*token)->next;
	if (curr && check_for_joining(tmp, curr))
		new_val = ft_strjoin(tmp->expand, curr->expand);
	else
		return (tmp->expand);
	while (curr)
	{
		tmp = curr->next;
		if (tmp && check_for_joining(curr, tmp))
			new_val = ft_strjoin(new_val, tmp->expand);
		else
			return (new_val);
		curr = curr->next;
	}
	*token = curr;
	return (NULL);
}

static void	*ft_join_token(t_list **token)
{
	char	*new_val;
	t_list	*tmp;
	t_list	*new_token;

	tmp = *token;
	new_val = join_word_type(&tmp);
	new_token = ft_lstnew((void *)new_val);
	tmp = non_word_token(*token);
	while (tmp)
	{
		new_val = join_word_type(&tmp);
		ft_lstadd_back(&new_token, ft_lstnew((void *)new_val));
		tmp = tmp->next;
	}
	return ((void *)new_token);
}

/*
** Have to make this function again
** Bad return (the new token list does not return like it should)
*/
void	*ft_recompose(t_list **token)
{
	t_list	*new_token;

	new_token = ft_join_token(token);
	return ((void *)new_token);
}
