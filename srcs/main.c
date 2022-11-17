/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 04:04:03 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/17 20:23:11 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_gc	*start;
int		g_status;

char	*ft_shellname(void)
{
	char	*tmp;

	tmp = get_pwd();
	tmp = ft_strjoin("\e[0;32m", tmp);
	tmp = ft_strjoin(tmp, ":$>\e[0m");
	return (tmp);
}

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
		printf("[\e[0;33m%s\e[0m]\n", (char *)token->val);
		token = token->next;
	}
	return ;
}

int	ft_minishell(t_env envp, char *s, int g_status)
{
	t_list	*token;
	t_cmd	*cmd;

	ft_add_history((void *)s);
	token = (t_list *)ft_lexer(s);
	if (!token)
		return (g_status);
	g_status = ft_parser(&token);
	if (g_status)
		return (g_status);
	ft_expander(&token, envp);
	cmd = ft_cmd(&token);
	if (cmd)
		g_status = ft_exec(&envp, cmd);
	return (g_status);
}

int	main(int ac, char **av, char **env)
{
	int		g_status;
	char	*s;
	t_env	envp;

	(void)ac;
	(void)av;
	s = NULL;
	printf("bb\b\b  \n");
	if (!*env)
		return (0);
	envp = ft_getenv(env);
	start = NULL;
	signal(SIGINT, intHandler);
	// signal(SIGQUIT, intHandler);
	signal(EOF, intHandler);
	g_status = 0;
	while (keepRunning)
	{
		s = readline((const char *)ft_shellname());
		if (s && *s && ft_not_only_space((void *)s))
		{
			g_status = ft_minishell(envp, s, g_status);
			if (g_status)
				g_status = 0;
		}
		free(s);
	}
	if (s)
		free(s);
	return (0);
}
