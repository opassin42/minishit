/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 03:11:54 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/04 17:24:38 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_in_env(t_list **lst, char *s)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (!ft_strcmp((char *)tmp->val, s))
			return (EXIT_FAILURE);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

static int	check_var_name(char *s)
{
	if (!s)
		return (EXIT_FAILURE);
	if ((ft_is_digit(*s) || !ft_isalpha(*s)) && *s != '_' && *s != '"')
		return (export_error(s), EXIT_FAILURE);
	if (!ft_strchr(s, '='))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	ft_add_to_env(t_env envp, t_list *token)
{
	void	*tmp;

	while (token)
	{
		tmp = token->val;
		if (check_var_name((char *)tmp))
			break ;
		if (!is_in_env(&envp.list, (char *)tmp))
		{
			tmp = (void *)expand(envp, tmp);
			ft_lstadd_back(&envp.list, ft_lstnew(tmp));
		}
		token = token->next;
	}
	return ;
}

int	ft_export(t_list *token, t_env envp)
{
	char	*cmd;
	t_list	*tmp;

	cmd = NULL;
	tmp = token;
	while (tmp)
	{
		cmd = (char *)tmp->val;
		if (!ft_strcmp(cmd, "export") && tmp->next)
			ft_add_to_env(envp, tmp->next);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
