/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:21:30 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/24 05:33:35 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	*define_arg(t_list *token)
{
	t_list	*tmp;
	t_list	*arg;

	token = token->next;
	if (!token)
		return (NULL);
	if (token->type == WORD)
		arg = ft_lstnew(token->val);
	else if (token->type == VOID)
		arg = NULL;
	else
		return (NULL);
	tmp = token->next;
	while (tmp)
	{
		if (tmp->type == VOID)
			tmp = tmp->next;
		if (tmp->type == WORD)
			ft_lstadd_back(&arg, ft_lstnew(tmp->val));
		else
			break ;
		tmp = tmp->next;
	}
	return (arg);
}

static char	**ft_arg(t_list *token)
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

static void	*create_cmd(t_list *token)
{
	t_cmd	*cmd;
	t_list	*tmp;

	if (token->type == WORD)
	{
		cmd = ft_new_cmd(token);
		if (!cmd)
			return (NULL);
		ft_init_cmd_struct(cmd, token->val);
		tmp = (t_list *)define_arg(token);
		cmd->arg = ft_arg(tmp);
		if (!cmd->arg)
			cmd->arg = (char **) NULL;
	}
	else
		return (NULL);
	return (cmd);
}

void	*ft_cmd(t_list **token)
{
	t_list	*tmp;
	t_cmd	*cmd;

	tmp = *token;
	cmd = (t_cmd *)create_cmd(tmp);
	if (!cmd)
		return (NULL);
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			tmp = tmp->next;
			if (tmp->type == VOID)
				tmp = tmp->next;
			ft_cmd_addback(&cmd, (t_cmd *)create_cmd(tmp));
		}
		tmp = tmp->next;
	}
	return ((void *)cmd);
}
