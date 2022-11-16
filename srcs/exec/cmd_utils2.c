/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 02:32:23 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/15 08:58:58 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_malloc_double_p(t_list *token)
{
	int		i;
	char	**param;

	if (!token)
		return ((char **) NULL);
	param = malloc(sizeof(char *) * (ft_lstsize(token) + 1));
	if (!param)
		return (NULL);
	i = 0;
	while (token)
	{
		param[i] = ft_strdup(token->val);
		if (!param[i])
			return ((char **) NULL);
		token = token->next;
		++i;
	}
	param[i] = 0;
	return (param);
}

// char	**join_param(char **param)
// {
// 	int		i;
// 	char	*s;
// 	char	**split;

// 	if (!param)
// 		return (NULL);
// 	i = 0;
// 	s = param[0];
// 	while (param[++i])
// 	{
// 		s = ft_strjoin(s, param[i]);
// 		if (!s)
// 			return (NULL);
// 	}
// 	split = ft_split(s, ' ');
// 	if (split)
// 		return (split);
// 	return (NULL);
// }

static t_list	*get_joined_token(t_list *token)
{
	char	*s;
	t_list	*new;

	s = token->expand;
	if (!s)
		return (NULL);
	token = token->next;
	while (token)
	{
		if (token->type != WORD)
			break ;
		s = ft_strjoin(s, token->expand);
		if (!s)
			return (NULL);
		token = token->next;
	}
	new = ft_lstnew((void *)s);
	if (!new)
		return (NULL);
	return (new);
}

void	*ft_tokenjoin(t_list **token)
{
	t_list	*tmp;
	t_list	*new;
	t_list	*elem;
	t_list	*curr;

	tmp = *token;
	new = NULL;
	elem = NULL;
	while (tmp)
	{
		curr = tmp;
		if (curr->type == VOID)
			curr = curr->next;
		if (curr->type == WORD)
		{
			elem = get_joined_token(curr);
			while (tmp->next)
			{
				if (tmp->type != WORD)
					break ;
				tmp = tmp->next;
			}
		}
		else
			elem = ft_lstnew((void *)curr->val);
		if (!elem)
			return (NULL);
		ft_lstadd_back(&new, elem);
		tmp = tmp->next;
	}
	return ((void *)new);
}
