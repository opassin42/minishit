/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 02:32:23 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/25 04:37:45 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_malloc_double_p(t_list *token)
{
	int		i;
	char	**param;

	if (!token)
		return ((char **) NULL);
	i = ft_lstsize(token);
	param = (char **)push_top(&start, (sizeof(char *) * (i + 1)));
	if (!param)
		return (gc_free(), NULL);
	i = 0;
	while (token)
	{
		hashing(token->val, 0, 1);
		param[i] = ft_strdup(token->val);
		if (!param[i])
			return (gc_free(), (char **) NULL);
		token = token->next;
		++i;
	}
	param[i] = 0;
	return (param);
}



// static t_list	*get_true_value(t_list *token)
// {
// 	char	*s;
// 	t_list	*new;

// 	s = token->expand;
// 	if (!s)
// 		return (NULL);
// 	token = token->next;
// 	while (token)
// 	{
// 		if (token->type != WORD)
// 			break ;
// 		s = ft_strjoin(s, token->expand);
// 		if (!s)
// 			return (NULL);
// 		token = token->next;
// 	}
// 	new = ft_lstnew((void *)s);
// 	if (!new)
// 		return (NULL);
// 	return (new);
// }

// void	*ft_tokenjoin(t_list **token)
// {
// 	t_list	*tmp;
// 	t_list	*new;
// 	t_list	*curr;

// 	tmp = *token;
// 	print_token(tmp);
// 	new = NULL;
// 	while (tmp)
// 	{
// 		curr = tmp;
// 		if (curr->type == VOID)
// 			curr = curr->next;
// 		if (curr && curr->type == WORD)
// 		{
// 			ft_lstadd_back(&new, get_true_value(curr));
// 			while (tmp->next)
// 			{
// 				if (tmp->type != WORD)
// 					break ;
// 				tmp = tmp->next;
// 			}
// 		}
// 		else
// 			ft_lstadd_back(&new, ft_lstnew((void *)curr->expand));
// 		tmp = tmp->next;
// 	}
// 	return ((void *)new);
// }
