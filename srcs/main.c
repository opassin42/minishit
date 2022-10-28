/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 04:04:03 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/27 22:33:31 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_add_history(void *s)
{
	if (s && ft_white_spaces(s))
		add_history(s);
	return ;
}

void	print_token(t_list *token)
{
	printf("\n\e[0;31mTOKEN :\e[0m\n");
	while (token)
	{
		// printf("[\e[0;33m%s - %s\e[0m]\n", (char *)token->val, token->expand);
		printf("[\e[0;33m%s\e[0m]\n", (char *)token->val);
		token = token->next;
	}
}

void	print_new_token(t_list **token)
{
	t_list	*tmp;

	tmp = *token;
	printf("\n\e[0;31mNEW_TOKEN :\e[0m\n");
	while (tmp)
	{
		printf("[\e[0;33m%s\e[0m:%d]\n", (char *)tmp->val, tmp->fct);
		tmp = tmp->next;
	}
}

void	print_cmd(t_cmd *cmd)
{
	int		i;
	char	**param;

	printf("\n\e[0;31mCMD :\e[0m\n");
	while (cmd)
	{
		printf("cmd : [\e[0;33m%s\e[0m]\n", (char *)cmd->name);
		if (cmd->param)
		{
			i = 0;
			param = cmd->param;
			while (param[i])
			{
				printf("\tparam[%d] : [\e[0;33m%s\e[0m]\n", i, param[i]);
				++i;
			}
		}
		cmd = cmd->next;
	}
}

void	ft_print_and_free(t_list **token)
{
	ft_free_token(token, free);
	printf("Syntax error.\n");
}

int	main(int ac, char **av, char **env)
{
	char	*s;
	char	*tmp;
	t_list	*token;
	t_env	envp;
	t_cmd	*cmd;

	(void)ac;
	(void)av;
	s = NULL;
	tmp = "\e[0;32mminishell:$>\e[0m ";
	envp = ft_getenv(env);
	while (42)
	{
		s = readline((const char *)tmp);
		if (s && *s && ft_not_only_space((void *)s))
		{
			ft_add_history((void *)s);
			token = (t_list *)ft_lexer(s);
			if (token)
			{
				if (!ft_parser(&token))
				{
					ft_expander(&token, envp);
					cmd = ft_cmd(&token);
					if (cmd)
						ft_exec(&envp, cmd);
						// print_cmd(cmd);
					print_token(token);
					ft_free_token(&token, free);
					token = NULL;
				}
				else
					ft_print_and_free(&token);
			}
		}
		free(s);
	}
	if (token)
		ft_free_token(&token, free);
	if (s)
		free(s);
	return (0);
}
