/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:21:30 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/23 19:16:16 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_init_cmd_struct(t_cmd *cmd, void *name)
{
	cmd->id = 0;
	cmd->err_no = 0;
	cmd->status = 0;
	cmd->pid = 0;
	cmd->fd_in = 0;
	cmd->fd_out = 0;
	cmd->rd = NULL;
	cmd->name = (char *)name;
	cmd->arg = NULL;
}

int	count_arg_nb(t_list *token)
{
	int	i;

	i = 0;
	token = token->next;
	while (token)
	{
		if (token->type != WORD && token->type != VOID)
			break ;
		++i;
		token = token->next;
	}
	return (i);
}

char	**malloc_arg(t_list *token)
{
	int		arg_nb;
	char	**param;

	arg_nb = count_arg_nb(token);
	if (!arg_nb)
		return (NULL);
	printf ("arg_nb = %d\n", arg_nb);
	param = malloc(sizeof(char *) * (arg_nb + 1));
	if (!param)
		return (NULL);
	token = token->next;
	if (token->type == VOID)
		token = token->next;
	param = (char **)fill_arg(token, param, arg_nb);
	if (!param)
		return (NULL);
	return (param);
}

void	*create_cmd(t_list *token)
{
	t_cmd	*cmd;

	if (token->type == WORD)
	{
		cmd = ft_new_cmd(token);
		if (!cmd)
			return (NULL);
		ft_init_cmd_struct(cmd, token->val);
		cmd->arg = malloc_arg(token);
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
