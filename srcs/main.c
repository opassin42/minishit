/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 04:04:03 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/17 18:53:54 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data	g_data;

static char	*ft_shellname(void)
{
	char *tmp;

	tmp = get_pwd();
	tmp = ft_strjoin("\e[0;32m", tmp);
	tmp = ft_strjoin(tmp, ":$>\e[0m");
	return (tmp);
}

static void	hash_var_value(t_var **var)
{
	t_var	*tmp;

	tmp = *var;
	while (tmp)
	{
		if (tmp->value)
			positive_hashing(tmp->value, 0);
		tmp = tmp->next;
	}
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
	hash_quote(&token);
	cmd = ft_cmd(&token);
	if (cmd)
	{
		status = ft_exec(envp, cmd);
	}
	return (status);
}

static int	ft_readline(t_env *envp, char *s)
{
	if (!s)
	{
		g_data.prompt = ft_shellname();
		s = readline((const char *)g_data.prompt);
	}
	if (!s)
		return (printf("exit\n"), g_data.status = -420);
	if (s && *s && *s != '\n')
	{
		if (envp)
			hash_var_value(&envp->var);
		g_data.status = ft_minishell(envp, s, g_data.status);
	}
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
	g_data.status = 0;
	if (isatty(STDIN_FILENO) == 0)
		return (gc_free(), 0);
	if (!*env)
		env = when_no_env();
	envp = ft_getenv(env);
	while (g_data.keeprunning)
	{
		init_sigflag();
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		g_data.status = ft_readline(envp, s);
		if (g_data.status == -420)
			break;
	}
	return (gc_free(), 0);
}
