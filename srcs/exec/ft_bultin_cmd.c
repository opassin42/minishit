/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bultin_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:31:33 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/20 10:06:37 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_init_cmd_struct(t_cmd *cmd)
{
	cmd->id = 0;
	cmd->err_no = 0;
	cmd->status = 0;
	cmd->pid = 0;
	cmd->fd_in = 0;
	cmd->fd_out = 0;
	cmd->name = 0;
	cmd->rd = 0;
	cmd->arg = 0;
}

t_cmd	*ft_new_cmd(t_list *token)
{
	char	*str;
	t_cmd	*cmd;

	str = (char *)token->val;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->name = str;
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

// void	*first_cmd(t_list **token)
// {
// 	t_list	*tmp;
// 	t_cmd	*cmd;

// 	tmp = *token;
// 	if (tmp->type == WORD)
// 	{
// 		cmd = ft_new_cmd(tmp);
// 		if (!cmd)
// 			return (NULL);
// 		return ((void *)cmd);
// 	}
// 	return (NULL);
// }

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
	int		i;
	int		arg_nb;
	char	**param;

	arg_nb = count_arg_nb(token);
	if (!arg_nb)
		return (NULL);
	param = malloc(sizeof(char *) * (arg_nb + 1));
	if (!param)
		return (NULL);
	i = 0;
	token = token->next;
	while (token && i < arg_nb)
	{
		param[i] = ft_strdup((char *)token->val);
		token = token->next;
		++i;
	}
	return (param);
}

void	*create_cmd(t_list *token)
{
	t_cmd	*cmd;

	if (token->type == WORD)
		cmd = ft_new_cmd(token);
	else
		return (NULL);
	cmd->arg = malloc_arg(token);
	return (cmd);
}

void	*ft_cmd(t_list **token)
{
	t_list	*tmp;
	t_cmd	*cmd;

	tmp = *token;
	cmd = create_cmd(tmp);
	if (!cmd)
		return (NULL);
	printf("SEG_VALUE1\n");
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			tmp = tmp->next;
			if (tmp)
			{
				if (tmp->type == VOID)
					tmp = tmp->next;
				ft_cmd_addback(&cmd, create_cmd(tmp));
			}
		}
		tmp = tmp->next;
	}
	printf("SEG_VALUE2\n");
	return ((void *)cmd);
}

void	ft_exec(t_list **token, t_env envp)
{
	t_list	*tmp;

	tmp = *token;
	if (!ft_strcmp(tmp->val, "env"))
		ft_env(&envp, tmp);
}

// void	ft_route(t_list **token, t_env envp, void (*f)())
// {
// 	// char	*s;
// 	// char	**tab;
// 	t_list	*tmp;

// 	tmp = *token;
// 	if (!ft_strcmp(tmp->val, "env"))
// 		ft_env(&envp, tmp);
// }
