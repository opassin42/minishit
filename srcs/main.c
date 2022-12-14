/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 04:04:03 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/14 06:31:45 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data	g_data;

char	*ft_shellname(void)
{
	char	*tmp;

	tmp = get_pwd();
	dup2(STDIN_FILENO, 0);
	dup2(STDIN_FILENO, 1);
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

int	ft_minishell(t_env *envp, char *s, int g_status)
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
	hash_quote(&token, -1);
	cmd = ft_cmd(&token);
	if (cmd)
	{
		g_status = ft_exec(envp, cmd);
		if (STDOUT_FILENO != 1)
			dup2(cmd->finalfdout, STDOUT_FILENO);
		if (STDIN_FILENO != 0)
			dup2(cmd->finalfdin, STDIN_FILENO);
	}
	return (g_status);
}

int	main(int ac, char **av, char **env)
{
	char	*s;
	t_env	*envp;

	(void)ac;
	(void)av;
	s = NULL;
	if (isatty(STDIN_FILENO) == 0)
		return (0);
	g_data = init_global();
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		return (0);
	if (signal(SIGQUIT, SIG_IGN))
		g_data.keeprunning = 1;
	init_signal();
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	envp = ft_getenv(env);
	while (g_data.keeprunning)
	{
		init_signal();
		s = readline((const char *)ft_shellname());
		if (s == NULL)
			return (gc_free(), printf("exit\n"), g_data.status);
		if (s && *s && ft_not_only_space((void *)s))
			g_data.status = ft_minishell(envp, s, g_data.status);
	}
	return (gc_free(), 0);
}
