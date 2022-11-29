/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:21:30 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/28 23:24:19 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	*ft_pre_cmd(t_list *token)
{
	char	*s;
	t_list	*tmp;

	s = (char *)join_token(token);
	if (!s)
		return (NULL);
	tmp = (t_list *)ft_tokeniser((void *)s, "|>< ");
	if (!tmp)
		return (NULL);
	ft_type(&tmp);
	return ((void *)tmp);
}

static void	*rm_space_token(t_list *token)
{
	t_list	*new;

	new = NULL;
	if (token->type == VOID)
		token = token->next;
	if (!token)
		return (NULL);
	new = ft_lstnew(token->val);
	if (!new)
		return (NULL);
	token = token->next;
	while (token)
	{
		if (token->type == VOID)
			token = token->next;
		if (token)
			ft_lstadd_back(&new, ft_lstnew(token->val));
		else
			break ;
		token = token->next;
	}
	return ((void *)new);
}

static void	assign_a_type(t_list **token)
{
	t_list	*tmp;

	tmp = *token;
	while (tmp)
	{
		tmp->type = -1;
		if (!word_type(tmp->val))
			tmp->type = WORD;
		else if (!pipe_type(tmp->val))
			tmp->type = PIPE;
		else if (!rd_type(tmp->val))
			tmp->type = RD;
		tmp = tmp->next;
	}
}

static void	*final_token(t_list **token)
{
	t_list	*new;
	t_list	*pre_cmd;
	t_list	*tmp;

	tmp = *token;
	if (tmp->type == VOID)
		tmp = tmp->next;
	pre_cmd = (t_list *)ft_pre_cmd(tmp);
	if (!pre_cmd)
		return (NULL);
	new = (t_list *)rm_space_token(pre_cmd);
	if (!new)
		return (NULL);
	assign_a_type(&new);
	return (new);
}

void	*ft_cmd(t_list **token)
{
	t_cmd	*cmd;
	t_list	*tmp;

	tmp = final_token(token);
	if (!tmp)
		return (NULL);
	hash_token(tmp);
	cmd = (t_cmd *)make_cmd(tmp);
	if (!cmd)
		return (NULL);
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			tmp = tmp->next;
			if (tmp)
				ft_cmd_addback(&cmd, (t_cmd *)make_cmd(tmp));
			else
				return ((void *)cmd);
		}
		tmp = tmp->next;
	}
	return ((void *)cmd);
}
