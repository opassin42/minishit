/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 04:04:03 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/19 23:53:47 by ccouliba         ###   ########.fr       */
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
		printf("[\e[0;33m%s - %s\e[0m]\n", (char *)token->val, token->expand);
		token = token->next;
	}
}

void	print_new_token(t_list *token)
{
	printf("\n\e[0;31mNEW_TOKEN :\e[0m\n");
	while (token)
	{
		printf("[\e[0;33m%s\e[0m]\n", (char *)token->val);
		token = token->next;
	}
}

void	print_double_p(char **arg)
{
	int	i;

	i = -1;
	printf("\n\e[0;31mCMD :\e[0m\n");
	while (arg[++i])
		printf("[\e[0;33m%s\e[0m]\n", arg[i]);
}

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	printf("\n\e[0;31mCMD :\e[0m\n");
	while (cmd)
	{
		printf("cmd : [\e[0;33m%s\e[0m]\n", (char *)cmd->name);
		while (cmd->arg[i])
		{
			printf("\targ : [\e[0;33m%s\e[0m]\n", cmd->arg[i]);
			if (!cmd->arg)
				continue ;
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
	tmp = "$> ";
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
					print_cmd(cmd);
					ft_exec(&token, envp);
					print_token(token);
					// print_new_token(new_token);
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
