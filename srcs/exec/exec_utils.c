/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:21:28 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/27 20:44:37 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*ft_new_cmd(t_list *token)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
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
		param[i] = ft_strdup((char *)token->val);
		if (!param[i])
			return ((char **) NULL);
		token = token->next;
		++i;
	}
	param[i] = 0;
	return (param);
}
