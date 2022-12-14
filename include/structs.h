/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:39:47 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/14 04:58:09 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <unistd.h>
# include <sys/types.h>

typedef struct s_gc
{
	void			*addr;
	struct s_gc		*next;
}				t_gc;

typedef struct s_data
{
	int				status;
	int				sigint;
	int				sigquit;
	pid_t			pid;
	volatile int	keeprunning;
	t_gc			*gc;
}				t_data;

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
	int				finalfdin;
	int				finalfdout;
	int				ret;
	int				fd_in;
	int				hdoc;
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
