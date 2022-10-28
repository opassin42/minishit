/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:39:55 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/27 22:31:27 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "inc.h"
# include "structs.h"
# include "defines.h"

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

int		is_heredoc(t_list *token);
int		is_rd_in(t_list *token);
int		is_rd_out(t_list *token);
int		is_append(t_list *token);
int		is_pipes(t_list *token);

int		init_syntaxer(t_syntaxer synt);
int		check_syntax(t_list *token, t_syntaxer synt);
int		ft_syntaxer(t_list **token, t_syntaxer synt);

int		init_function(t_func fct);
void	ft_function(t_list **token, t_func fct);

int		ft_parser(t_list **token);

/******************************************************************************/
/*********************************  EXPANDING  ********************************/
/******************************************************************************/
int		ft_alnum_underscore(int c);
int		check_simple_quotes(char *s);
int		ft_get_dollar_pos(char *s);
char	*find_value(t_env *envp, char *var_name);

void	ft_expander(t_list **token, t_env envp);
void	*ft_recompose(t_list **token);
/*
** QUOTES REMOVING (after expander)
*/
int		ft_check_quotes(t_list *token);
int		ft_open_quotes(t_list *token);
void	*ft_rm_quotes(t_list *token);
void	ft_quotes(t_list **token);

/******************************************************************************/
/***********************************  ENV  ************************************/
/******************************************************************************/
t_env	ft_init_env(char **env);
t_var	*ft_init_var(t_list **env_list);

void	find_in_env(t_env *envp, char *var_name, char *(*f)());
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
int		ft_cd(char *path);
int		ft_export(t_list *token, t_env envp);
int		ft_env(t_env *envp, t_cmd *cmd);

/* Exec */
t_cmd	*ft_new_cmd(t_list *token);
t_cmd	*ft_last_cmd(t_cmd *cmd);
void	ft_cmd_addback(t_cmd **cmd, t_cmd *new_cmd);
char	**ft_malloc_double_p(t_list *token);


void	*ft_cmd(t_list **token);
int		ft_non_builtin(t_env *envp, t_cmd *cmd, char **path);
void	ft_router(t_env *envp, t_cmd *cmd);
void	ft_exec(t_env *envp, t_cmd *cmd);

/******************************************************************************/
/**********************************  UTILS  ***********************************/
/******************************************************************************/
/* Mem utils */
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memmove(void *dest, void *src, size_t n);
void	*ft_realloc(char *s, size_t new_len);
void	*ft_strjoin_char(char *s1, char c);

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

/******************************************************************************/
/**********************************  ERRORS  **********************************/
/******************************************************************************/
/* Builtin errors*/
void	export_error(char *s);

#endif
