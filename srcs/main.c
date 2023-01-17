/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 04:04:03 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/27 04:12:04 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data	g_data;


char	*ft_shellname(void)
{
	char	*tmp;

	tmp = get_pwd();
	// dup2(STDIN_FILENO, 0);
	// dup2(STDIN_FILENO, 1);
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
	if (cmd){
		status = ft_exec(envp, cmd);
	}
	return (status);
}

int	ft_readline(t_env *envp, char *s)
{
	s = readline((const char *)ft_shellname());
	if (s == NULL)
		return (127);
	if (s && *s && *s != '\n')
		return (ft_minishell(envp, s, g_data.status));
	return (1);
}

int	main(int ac, char **av, char **env)
{
	char	*s;
	t_env	*envp;

	(void)ac;
	(void)av;
	s = NULL;
	init_global(&g_data);
	g_data.status = 0;
	if (isatty(STDIN_FILENO) == 0)
		return (gc_free(), 0);
	if (*env)
		envp = ft_getenv(env);
	else
		envp = NULL;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	g_data.sigint = 0;
	g_data.sigquit = 0;
	while (g_data.keeprunning)
	{
		s = readline((const char *)ft_shellname());
		if (!s)
			break;
		if (s && *s != '\n')
			ft_minishell(envp, s, g_data.status);
		if (g_data.status == 127)
			g_data.keeprunning = 0 ;
	}
	printf("exit\n");
	return (gc_free(), 0);
}
