/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:39:47 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/02 06:44:36 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_gc
{
	void			*addr;
	struct s_gc		*next;
}				t_gc;

typedef enum s_type
{
	PIPE,
	RD,
	VOID,
	WORD
}				t_type;

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
	int				id;
	int				pid;
	int				status;
	int				fd_in;
	int				fd_out;
	int				append;
	char			*outfile;
	char			*infile;
	char			*delim;
	char			*name;
	char			**param;
	char			**arg;
	char			*bin;
	char			**heredoc;
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

typedef int(*t_func[5])(t_list *);
typedef int(*t_syntaxer[4])(t_list *);
typedef int(*t_exec[7])(t_env *, t_cmd *);

#endif
