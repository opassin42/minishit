/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 04:04:03 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/11 06:01:35 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_gc	*start;
int		g_status;

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

	if (!s)
		return (EXIT_SUCCESS);
	add_history((void *)s);
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

int	ft_readline(t_env *envp, char *s)
{
	g_status = 0;
	s = readline((const char *)ft_shellname());
	if (!s)
		return (gc_free(), printf("exit\n"), g_status = -42);
	if (s && *s && *s != '\n')
		g_status = ft_minishell(envp, s, g_status);
	if (s)
		free(s);
	return (g_status);
}

int	main(int ac, char **av, char **env)
{
	char	*s;
	t_env	*envp;

	(void)ac;
	(void)av;
	s = NULL;
	start = NULL;
	g_status = 0;
	if (isatty(STDIN_FILENO) == 0)
		keepRunning = 1;
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		return (EXIT_FAILURE);
	if (signal(SIGQUIT, SIG_IGN))
		keepRunning = 1;
	if (*env)
		envp = ft_getenv(env);
	while (keepRunning)
	{
		g_status = ft_readline(envp, s);
		if (g_status == -42)
			return (0);
	}
	return (gc_free(), 0);
}
