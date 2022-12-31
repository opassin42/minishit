/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 04:04:03 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/31 13:46:14 by ccouliba         ###   ########.fr       */
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

// void	*definitive_value_change(char *s)
// {
// 	if (!s)
// 		return (NULL);
// 	if (*s == ' ' || *s == '\t')
// 	{
// 		if (*s == ' ')
// 			++s;
// 		else if (*s == '\t')
// 			*s = ' ';
// 		while (*s == ' ')
// 			++s;
// 	}
// 	while (*s)
// 	{
		
// 		++s;	
// 	}
// }

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
	//Have to change the token->val RIGHT HERE ; depending on quote flag HERE
	cmd = ft_cmd(&token);
	if (cmd)
	{
		status = ft_exec(envp, cmd);
		dup2(cmd->fd_out, STDOUT_FILENO);
		dup2(cmd->fd_in, STDIN_FILENO);
	}
	return (status);
}

int	ft_readline(t_env *envp, char *s)
{
	s = readline((const char *)ft_shellname());
	if (!s)
		return (printf("exit\n"), g_data.status = -420);
	if (s && *s && *s != '\n')
		g_data.status = ft_minishell(envp, s, g_data.status);
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
		return (gc_free(), 0);
	envp = ft_getenv(env);
	while (g_data.keeprunning)
	{
		g_data.sigint = 0;
		g_data.sigquit = 0;
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		g_data.status = ft_readline(envp, s);
		if (g_data.status == -420)
			return (gc_free(), 0);
	}
	return (gc_free(), 0);
}
