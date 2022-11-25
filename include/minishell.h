/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:39:55 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/25 03:01:31 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "inc.h"
# include "defines.h"
# include "structs.h"

extern int			g_status;
extern t_gc			*start;
static volatile int	keepRunning = 1;

/******************************************************************************/
/**********************************  INITS  ***********************************/
/******************************************************************************/
// t_flag	ft_init_flag(void);

/******************************************************************************/
/**********************************  LEXING  **********************************/
/******************************************************************************/
int		ft_flag_char(int c, char *delim);
void	*ft_meta_quotes(char *s, int c);
void	*ft_meta_char(char *s, int c);
void	*ft_dollar_char(char *s);
void	*ft_normal_char(char *s, char *m_char);
int		ft_not_only_space(void *p);

int		word_type(void *p);
int		pipe_type(void *p);
int		rd_type(void *p);

void	hashing(char *s, int c, int factor);
void	*ft_tokeniser(void *arg, char *delim);
void	ft_type(t_list **token);
void	*ft_lexer(void *arg);

/******************************************************************************/
/**********************************  PARSING  *********************************/
/******************************************************************************/
int		check_quotes_word(t_list *token);
int		wrong_next(t_list *token);
int		wrong_pipe(t_list *token);
int		wrong_rd(t_list *token);

void	syntax_error(char *token, char *err_msg, int fd, void (*f)());
int		ft_syntaxer(t_list **token, t_syntaxer synt);

// void	*definitive_token(char *s, char *m_char);
// void	*make_definitive_token(t_list *token);
int		ft_parser(t_list **token);

/******************************************************************************/
/*********************************  EXPANSION  ********************************/
/******************************************************************************/
int		ft_alnum_underscore(int c);
int		check_quotes(char *s, int c);
int		ft_get_dollar_pos(char *s);
void	*var_name(char *str, int start);
char	*find_value(t_env *envp, char *var_name);

char	*expand(t_env envp, char *s);
void	*ft_tokenjoin(t_list **token);
void	ft_expander(t_list **token, t_env envp);
char	*ft_recompose(t_env envp, char *s);
// char	*ft_assemble(t_env envp, t_list *token, char *first_val);
/*
** QUOTES REMOVING (after expander)
*/
void	expand_quote_flag(t_list *token);
char	*remove_quotes(t_list *token);

int		ft_check_quotes(t_list *token);
int		ft_open_quotes(t_list *token);
void	*ft_rm_quotes(t_list *token);
void	ft_quotes(t_list **token);

/******************************************************************************/
/***********************************  ENV  ************************************/
/******************************************************************************/
t_env	ft_init_env(char **env);
t_var	*ft_init_var(t_list **env_list);

// void	find_in_env(t_env *envp, char *var_name, char *(*f)());
char	*get_in_env(t_env *envp, char *name);
void	up_in_env(t_env *envp, char *var_name, char *s);
t_env	ft_getenv(char **env);

char	*ft_var_name(char *s);
t_var	*ft_new_var(t_list *token);
t_var	*ft_last_var(t_var *var);
void	ft_var_addback(t_var **var, t_var *new_var);
int		ft_size_of_env(t_var *var);

/******************************************************************************/
/*********************************  BUILT_IN  *********************************/
/******************************************************************************/
int		ft_pwd(t_env *envp, t_cmd *cmd);
int		ft_echo(t_env *envp, t_cmd *cmd);
int		ft_cd(t_env *envp, t_cmd *cmd);
int		ft_env(t_env *envp, t_cmd *cmd);
int		ft_unset(t_env *envp, t_cmd *cmd);
int		ft_exit(t_env *envp, t_cmd *cmd);
/* Unset */
int		get_nb_var(t_cmd *cmd);
void	ft_free_var(t_var *var);
void	ft_delete_var(t_env *envp, char *var_name);

/* Export*/
// int		is_valid_name(char *str);
char	*split_name(t_cmd *cmd, int i);
char	*split_value(t_cmd *cmd, int i);
t_var	*ft_new_var_env(t_cmd *cmd, int i);
int		ft_export(t_env *envp, t_cmd *cmd);
void	ft_export_env(t_var *var);

/* Exec */
t_cmd	*ft_new_cmd(t_list *token);
t_cmd	*ft_last_cmd(t_cmd *cmd);
void	ft_cmd_addback(t_cmd **cmd, t_cmd *new_cmd);
char	**join_param(char **param);
char	**ft_malloc_double_p(t_list *token);

char	*get_pwd(void);
int		is_alphanum(t_upvarenv *upvarenv);
int		ft_no_home(t_upvarenv *upvarenv);

void	*join_token(t_list *token);
void	*ft_pre_cmd(t_list **token);
void	*ft_cmd(t_list **token);

int		ft_non_builtin(t_env *envp, t_cmd *cmd, char **path);
int		ft_router(t_env *envp, t_cmd *cmd);
int		ft_exec(t_env *envp, t_cmd *cmd);

/******************************************************************************/
/**********************************  UTILS  ***********************************/
/******************************************************************************/
/* Mem utils */
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memmove(void *dest, void *src, size_t n);
void	*ft_realloc(char *s, size_t new_len);
void	*ft_strjoin_char(char *s1, char c);

/* Print utils */
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/* Str utils */
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
int		ft_is_digit(int c);
int		ft_isalpha(int c);
int		ft_white_spaces(void *p);
int		ft_strlen(char *s);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *s);
char	**ft_split(char *s, char c);
char	**free_double_p(char **s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, int start, size_t len);
char	*ft_strtrim(char *s1, char *set);

/* List utils */
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lst_prevlast(t_list **list);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*));

/* Minishell utils */
void	print_token(t_list *token);
void	ft_print_env(t_var *var);
void	ft_free_token(t_list **token, void (*clr)(void*));
void	ft_add_history(void *s);
void	*ft_void_skipper(t_list **token);
void	*push_top(t_gc **head, size_t data_size);
void	printList(t_gc	*node);
void	gc_free(void);
void	ft_pop_in_gc(t_gc **start, void *p);

/******************************************************************************/
/**********************************  ERRORS  **********************************/
/******************************************************************************/
/* Builtin errors*/
void	export_error(char *s);

/******************************************************************************/
/**********************************  SIGNALS  *********************************/
/******************************************************************************/
void	sig_handler(int dummy) ;

#endif
