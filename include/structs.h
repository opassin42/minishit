/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:39:47 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/20 20:30:04 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_gc
{
	void			*addr;
	struct s_gc		*next;
}				t_gc;

typedef struct s_data
{
	int				cmdsize;
	int				status;
	int				rd_error;
	int				prev;
	int				pfd[2];
	char			*prompt;
	pid_t			pid;
	t_gc			*gc;
	volatile int	keeprunning;
}				t_data;

typedef enum s_type
{
	PIPE,
	RD,
	VOID,
	WORD
}				t_type;

typedef struct s_rd
{
	int				flag;
	char			*file;
	struct s_rd		*next;
}				t_rd;

typedef struct s_list
{
	int				exp_flag;
	int				quote;
	void			*val;
	char			*expand;
	char			*rest;
	t_type			type;
	struct s_list	*next;
}				t_list;

typedef struct s_var
{
	int				id;
	char			*name;
	char			*value;
	struct s_var	*next;
}				t_var;

typedef struct s_env
{
	char			**tab;
	t_list			*list;
	t_var			*var;
}				t_env;

typedef struct s_cmd
{
	int				i;
	int				id;
	int				pid;
	int				ret;
	int				fd[2];
	int				hdoc;
	int				append;
	char			*outfile;
	char			*infile;
	char			*name;
	char			**param;
	char			**arg;
	char			*bin;
	t_rd			*rd;
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
}				t_upvarenv;

typedef int(*t_syntaxer[4])(t_list *);
typedef int(*t_exec[7])(t_env *, t_cmd *);

#endif
