/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 04:04:03 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/26 15:45:41 by ccouliba         ###   ########.fr       */
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

static int	ft_minishell(t_env *envp, char *s, int status)
{
	t_list	*token;
	t_cmd	*cmd;

	if (!s)
		return (EXIT_SUCCESS);
	add_history((void *)s);
	token = (t_list *)ft_lexer(s);
	if (!token)
		return (status);
	status = ft_parser(&token);
	if (status)
		return (status);
	ft_expander(&token, envp);
	hash_quote(&token, -1);
	cmd = ft_cmd(&token);
	if (cmd)
	{
		status = ft_exec(envp, cmd);
		if (STDOUT_FILENO != 1)
			dup2(cmd->finalfdout, STDOUT_FILENO);
		if (STDIN_FILENO != 0)
			dup2(cmd->finalfdin, STDIN_FILENO);
	}
	return (status);
}

int	ft_readline(t_env *envp, char *s)
{
	s = readline((const char *)ft_shellname());
	if (!s)
		return (gc_free(), printf("exit\n"), g_data.status = -42);
	if (s && *s && *s != '\n')
		g_data.status = ft_minishell(envp, s, g_data.status);
	if (s)
		free(s);
	return (g_data.status);
}

int	main(int ac, char **av, char **env)
{
	char	*s;
	t_env	*envp;

	(void)ac;
	(void)av;
	s = NULL;
	g_data = init_global();
	if (isatty(STDIN_FILENO) == 0)
		g_data.keeprunning = 1;
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		return (EXIT_FAILURE);
	if (signal(SIGQUIT, SIG_IGN))
		g_data.keeprunning = 1;
	if (*env)
		envp = ft_getenv(env);
	while (g_data.keeprunning)
	{
		g_data.status = ft_readline(envp, s);
		if (g_data.status == -42)
			return (0);
	}
	return (gc_free(), 0);
}
