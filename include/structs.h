/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:39:47 by ccouliba          #+#    #+#             */
/*   Updated: 2022/10/19 19:10:49 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef int(*t_lexer[])(void *);
typedef int(*t_parser[])(void *);
typedef int(*t_exec[])(void *);

typedef struct s_file
{
	int				status;
	char			*ext;
	char			*name;
}				t_file;

typedef struct s_pipe
{
	int				status;
}					t_pipe;

typedef struct s_rd
{
	int				status;
	int				rd_in;
	int				rd_out;
	int				h_doc;
	char			*redir;
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
	ARG,
	CMD,
	FILES,
	RD_IN,
	RD_OUT,
	H_DOC,
	APPEND
}				t_function;

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
	// char			*value;
	char			**tab;
	t_list			*list;
	t_var			*var;
}				t_env;

typedef struct s_cmd
{
	int				id;
	int				errnb;
	int				status;
	int				pid;
	int				fd_in;
	int				fd_out;
	char			*name;
	char			*rd;
	char			**arg;
	struct s_cmd	*next;
}				t_cmd;

#endif
