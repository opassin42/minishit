/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:21:28 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/02 05:04:40 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*ft_new_cmd(t_list *token)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)push_top(&start, sizeof(t_cmd));
	if (!cmd)
		return (gc_free(), NULL);
	cmd->name = (char *)token->val;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*ft_last_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		while (cmd->next)
			cmd = cmd->next;
	}
	return (cmd);
}

void	ft_cmd_addback(t_cmd **cmd, t_cmd *new_cmd)
{
	if (new_cmd)
	{
		if (*cmd)
			ft_last_cmd(*cmd)->next = new_cmd;
		else
			*cmd = new_cmd;
	}
}

void	*join_token(t_list *token)
{
	char	*s;
	t_list	*tmp;

	tmp = token;
	s = tmp->expand;
	tmp = tmp->next;
	while (tmp)
	{
		s = ft_strjoin(s, tmp->expand);
		if (!s)
			return (NULL);
		tmp = tmp->next;
	}
	return ((void *)s);
}

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
		param[i] = ft_strdup(token->val);
		if (!param[i])
			return (gc_free(), (char **) NULL);
		token = token->next;
		++i;
	}
	param[i] = 0;
	return (param);
}
