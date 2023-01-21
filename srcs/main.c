/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 04:04:03 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/21 04:03:31 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data	g_data;

static void	textgenerator(void)
{
	printf(BHBLU"\n\n\n ____ ____ ____ ____ ____ ____ ____ ____ \n"RESET);
	printf(BHBLU"||  |||  |||  |||  |||  |||  |||  |||  || \n"RESET);
	printf(BHGRN"||M |||I |||N |||I ||| S||| H||| I||| T|| \n"RESET);
	printf(BHYEL"||__|||__|||__|||__|||__|||__|||__|||__|| \n"RESET);
	printf(BHRED"|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\| \n\n\n"RESET);
}

static char	*ft_shellname(void)
{
	char	*tmp;

	tmp = get_pwd();
	if (!tmp)
		return (NULL);
	tmp = ft_strjoin(GRNB"\33[1;35m", tmp);
	if (!tmp)
		return (NULL);
	tmp = ft_strjoin(tmp, "\33[5;35m🔥\033[m\n\033[1;5;34;0m ↳ \033[0m"RESET);
	if (!tmp)
		return (NULL);
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
	hash_quote(&token);
	cmd = ft_cmd(&token);
	if (cmd)
	{
		cmd_index(&cmd);
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
		if (!s)
			return (printf("exit\n"), g_data.status = -420);
	}
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
	textgenerator();
	if (!*env)
		env = when_no_env();
	envp = ft_getenv(env);
	while (g_data.keeprunning)
	{
		signal(SIGINT, parent_handler);
		signal(SIGQUIT, parent_handler);
		g_data.status = ft_readline(envp, s);
		if (g_data.status == -420)
			break ;
	}
	return (gc_free(), 0);
}
