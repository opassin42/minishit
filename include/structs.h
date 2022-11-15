/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:39:47 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/15 17:37:24 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_file
{
	int				status;
	char			*ext;
	char			*name;
}				t_file;

typedef struct s_pipe
{
	int				id;
	int				status;
}					t_pipe;

typedef struct s_rd
{
	int				status;
	int				rd_in;
	int				rd_out;
	int				heredoc;
	char			*redir;
	t_file			file;
}				t_rd;

typedef enum s_type
{
	PIPE,
	RD,
	VOID,
	WORD
}				t_type;

typedef enum s_function
{
	H_DOC,
	RD_IN,
	RD_OUT,
	APPEND,
	PIPES,
	CMD,
	ARG,
	ZERO
}				t_function;

typedef struct s_gc
{
    void    *addr;
    struct s_gc  *next;
} t_gc;

typedef struct s_list
{
	int				exp_flag;
	void			*val;
	char			*expand;
	t_type			type;
	t_function		fct;
	struct s_list	*next;
}				t_list;

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}				t_var;

typedef struct s_env
{
	int				shlvl;
	char			**tab;
	t_list			*list;
	t_var			*var;
}				t_env;

typedef struct s_cmd
{
	int				id;
	int				pid;
	int				err_no;
	int				status;
	int				fd_in;
	int				fd_out;
	char			*rd;
	char			*name;
	char			**param;
	char			**arg;
	char			*bin;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_builtin
{
	char			*key;
	int				(*f)();
}				t_builtin;

typedef struct s_upvarenv
{
	char	*oldpwd;
	char	*pwd;
	char	*tmp;
	char	*path;
}	t_upvarenv;

typedef int(*t_func[5])(t_list *);
typedef int(*t_syntaxer[4])(t_list *);
typedef int(*t_exec[7])(t_env *, t_cmd *);

#endif
