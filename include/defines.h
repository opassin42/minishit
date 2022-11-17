/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:39:52 by ccouliba          #+#    #+#             */
/*   Updated: 2022/11/15 17:35:42 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define PROMPT "$> "
# define EXIT "exit"
# define R_D "><"
# define DELIM "|><"
# define M_CHAR "|><\"' "
# define QUOTE_LIST "'\""
# define FAIL -1
# define SUCCESS 0
# define ERRNO_1 "syntax error near unexpected token"
# define ERRNO_2 "command not found"
# define ERRNO_3 "no such file or directory"
/*
** ANSI COLORS
*/

# define RED "\e[1;31m"
# define BK_RED "\e[5;31m"

# define WHITE "\e[1;37m"
# define BLUE "\e[1;34m"
# define GREEN "\e[1;32m"
# define GREY "\e[1;30m"
# define YELLOW "\e[1;33m"
# define PURPLE "\e[1;35m"
# define CYAN "\e[1;36m"
# define END "\e[0m"

#endif
