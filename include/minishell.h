/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:39:55 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/20 23:52:54 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "inc.h"
# include "structs.h"
# include "defines.h"

extern t_data	g_data;

/******************************************************************************/
/**********************************  INITS  ***********************************/
/******************************************************************************/
void	init_sigflag(void);
t_data	init_global(void);
void	init_builtin(t_builtin *builtin);

/******************************************************************************/
/**********************************  LEXING  **********************************/
/******************************************************************************/
int		ft_flag_char(int c, char *delim);
int		ft_not_only_space(void *p);
void	*ft_meta_quotes(char *s, int c);
void	*ft_meta_char(char *s, int c);
void	*ft_dollar_char(char *s);
void	*ft_normal_char(char *s, char *m_char);

int		word_type(void *p);
int		pipe_type(void *p);
int		rd_type(void *p);

void	*ft_tokeniser(void *arg, char *delim);
void	ft_type(t_list **token);
void	*ft_lexer(void *arg);

/******************************************************************************/
/**********************************  PARSING  *********************************/
/******************************************************************************/
int		ft_parser(t_list **token);

int		ft_syntaxer(t_list **token, t_syntaxer synt);
void	syntax_error(char *token, char *err_msg, int fd, void (*f)());

int		ft_open_quotes(t_list *token);
int		ft_check_quotes(t_list *token);
int		check_quotes_word(t_list *token);

/******************************************************************************/
/*********************************  EXPANSION  ********************************/
/******************************************************************************/
void	ft_expander(t_list **token, t_env *envp);

char	*find_value(t_env *envp, char *var_name);
char	*expand(t_env *envp, char *s);
char	*ft_recompose(t_env *envp, char *s);

void	positive_hashing(char *s, int c);
void	negative_hashing(char *s, int c);
void	hash_token(t_list *token);
void	hash_quote(t_list **token);
void	hash_var_value(t_var **var);

int		ft_alnum_underscore(int c);
int		check_quotes(char *s, int c);
int		ft_get_dollar_pos(char *s);
void	expand_quote_flag(t_list *token);
char	*remove_quotes(t_list *token);

/******************************************************************************/
/***********************************  ENV  ************************************/
/******************************************************************************/
char	*get_in_env(t_env *envp, char *name);
void	up_in_env(t_env *envp, char *var_name, char *s);
t_env	*ft_getenv(char **env);

char	**when_no_env(void);
char	*ft_var_name(char *s);
t_var	*ft_new_var(t_list *token);
t_var	*ft_last_var(t_var *var);
void	ft_var_addback(t_var **var, t_var *new_var);

/******************************************************************************/
/*********************************  BUILT_IN  *********************************/
/******************************************************************************/
int		ft_pwd(t_env *envp, t_cmd *cmd);
int		ft_echo(t_env *envp, t_cmd *cmd);
int		ft_cd(t_env *envp, t_cmd *cmd);
int		ft_env(t_env *envp, t_cmd *cmd);
int		ft_unset(t_env *envp, t_cmd *cmd);
int		ft_exit(t_env *envp, t_cmd *cmd);

char	*get_pwd(void);
int		is_alphanum(t_upvarenv *upvarenv);
int		ft_no_home(t_upvarenv *upvarenv);
void	update_env(t_env *envp, t_upvarenv *upvarenv, void (*f)());
int		replace_if_exists(t_env *envp, t_var *new_var);

/* Unset */
int		get_nb_var(t_cmd *cmd);
void	ft_free_var(t_var *var);
void	ft_delete_var(t_env *envp, char *var_name);

/* Export*/
char	*split_name(t_cmd *cmd, int i);
char	*split_value(t_cmd *cmd, int i);
t_var	*ft_new_var_env(t_cmd *cmd, int i);
int		ft_export(t_env *envp, t_cmd *cmd);
void	ft_export_env(t_var *var);

/* Exec */
void	*ft_cmd(t_list **token);
void	*make_cmd(t_list *token);
void	*first_cmd(t_list **token);
int		check_cmd(char *s);
void	cmd_index(t_cmd **cmd);

t_cmd	*ft_new_cmd(t_list *token);
t_cmd	*ft_last_cmd(t_cmd *cmd);
void	ft_cmd_addback(t_cmd **cmd, t_cmd *new_cmd);
void	*join_token(t_list *token);
char	**ft_malloc_double_p(t_list *token);

int		ft_exec(t_env *envp, t_cmd *cmd);
int		ft_process(t_env *envp, t_cmd *cmd);
void	router(t_env *envp, t_cmd *cmd, t_builtin *builtin);
int     which_builtin(t_builtin *builtin, t_cmd *cmd);
void	exec_builtin(t_env *envp, t_cmd *cmd, t_builtin *builtin);
void	exec_non_builtin(t_env *envp, t_cmd *cmd);
char	*binary_file(t_cmd *cmd, char **path);

void	input_without_cmd(t_list **token);
void	init_rd(t_cmd *cmd, t_list *token);

/******************************************************************************/
/**********************************  UTILS  ***********************************/
/******************************************************************************/
/* Mem utils */
void	*ft_memcpy(void *dest, const void *src, size_t n);

/* Print utils */
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);

/* Char_is utils */
char	*ft_itoa(int n);
int		ft_is_digit(int c);
int		ft_isalnum(int a);

/* Str utils */
int		ft_strlen(char *s);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *s);
char	**ft_split(char *s, char c);
char	**free_double_p(char **s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, int start, size_t len);

/* List utils */
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lst_prevlast(t_list **list);
void	ft_lstadd_back(t_list **alst, t_list *new);

/* Minishell utils */
void	print_token(t_list *token);
void	ft_print_env(t_var *var);
void	ft_free_token(t_list **token, void (*clr)(void*));
void	ft_add_history(void *s);
void	*ft_void_skipper(t_list **token);
void	*push_top(t_gc **head, size_t data_size);
void	printlist(t_gc	*node);
void	gc_free(void);
void	ft_pop_in_gc(t_gc **gc, void *p);

/******************************************************************************/
/**********************************  ERRORS  **********************************/
/******************************************************************************/
/* Builtin errors*/
void	export_error(char *s);
void	exec_error(char *token, char *err_msg, int fd, void (*f)());

/******************************************************************************/
/**********************************  SIGNALS  *********************************/
/******************************************************************************/

void	child_handler(int sig);
void	parent_handler(int sig);

/******************************************************************************/
/**********************************  PIPES    *********************************/
/******************************************************************************/
int		count_pipe(t_cmd *cmd);
void	p_father(t_cmd *cmd);
void	p_child(t_env *envp, t_cmd *cmd);
void	ft_waitpid(t_cmd *cmd);
int		ft_cmdsize(t_cmd *cmd);


void	init_rd_struct(t_cmd *cmd, t_list *token);
void	open_files(t_cmd *cmd);
int		check_access(t_env *envp, t_cmd *cmd, char **path);

#endif
