/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:39:52 by ccouliba          #+#    #+#             */
/*   Updated: 2023/01/13 16:55:29 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define STDIN 0
# define STDOUT 1

# define PROMPT "$> "

# define FAIL -1
# define SUCCESS 0
# define EXIT "exit"

/*
** List of tokenizable
*/
# define R_D "><"
# define DELIM "|><"
# define M_CHAR "|><\"' "
# define QUOTE_LIST "'\""

/*
** Messages error
*/
# define ERRNO_1 "Syntax error near unexpected token"
# define ERRNO_2 "Command not found"
# define ERRNO_3 "No such file or directory"
# define ERRNO_ENV "There is no printable environment"

# define MISSING_ENV "No env ; Cannot export variable.\n"

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
