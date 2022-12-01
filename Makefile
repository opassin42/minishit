# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/12 20:03:20 by ccouliba          #+#    #+#              #
#    Updated: 2022/12/01 06:12:47 by ccouliba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = @gcc

CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

include .color_code.txt

SRCS =	srcs/main.c \
		srcs/built_in/ft_env.c \
		srcs/built_in/ft_export.c \
		srcs/built_in/ft_unset.c \
		srcs/built_in/ft_echo.c \
		srcs/built_in/ft_pwd.c \
		srcs/built_in/ft_cd.c \
		srcs/built_in/ft_exit.c \
		srcs/built_in/ft_error.c \
		srcs/lexer/ft_tokeniser.c \
		srcs/lexer/ft_type.c \
		srcs/lexer/ft_lexer.c \
		srcs/lexer/ft_lexer_utils.c \
		srcs/parser/ft_parser.c \
		srcs/parser/ft_syntaxer.c \
		srcs/parser/ft_parser_utils.c \
		srcs/expander/ft_expander.c \
		srcs/expander/ft_expander_utils.c \
		srcs/expander/ft_recompose.c \
		srcs/env/ft_getenv.c \
		srcs/env/ft_find_in_env.c \
		srcs/env/getenv_utils.c \
		srcs/exec/cmd/ft_make_cmd.c \
		srcs/exec/cmd/ft_cmd.c \
		srcs/exec/cmd/cmd_utils.c \
		srcs/exec/ft_router.c \
		srcs/exec/ft_signal.c \
		srcs/exec/ft_exec.c \
		srcs/exec/hashing.c \
		utils/ft_init.c \
		utils/ft_split.c \
		utils/lib_utils_0.c \
		utils/lib_utils.c \
		utils/lib_utils2.c \
		utils/lib_utils3.c \
		utils/lib_utils4.c \
		utils/list_utils.c \
		utils/list_utils2.c \
		utils/ft_builtins_utils.c \
		utils/ft_garbage_collector.c \
		utils/signals.c
		
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		@echo "[$(_BLUE)!$(_END)] Rules :\t[$(_BLUE)all$(_END)] [$(_BLUE)clean$(_END)] [$(_BLUE)fclean$(_END)] [$(_BLUE)re$(_END)] [$(_BLUE)leak$(_END)] [$(_BLUE)debug$(_END)]"
		@echo -n "\n"
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline
		@echo "[$(_GREEN)!$(_END)] Compilation ... 	  [$(_BK_GREEN)SUCCESS$(_END)]"
		@echo "[$(_GREEN)!$(_END)] Creating .out ... 	  [$(_BK_GREEN)SUCCESS$(_END)]"
		@bash .script_bar.sh
		@echo "[$(_YELLOW)!$(_END)] Exec name :		[$(_YELLOW)$(NAME)$(_END)]"

%o: %.c
	$(CC) $(FLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJS)
	@echo "[$(_RED)!$(_END)] Removing objects ...  [$(_BK_GREEN)SUCCESS$(_END)]"

fclean: clean
	@rm -f $(NAME)
	@echo "[$(_RED)!$(_END)] Removing .out ...	  [$(_BK_GREEN)SUCCESS$(_END)]"

re: fclean all

leak: re
	@echo "				$(_BG_CYAN)LEAK TEST$(_END) (valgrind)"
	@valgrind ./$(NAME)
# @valgrind --suppressions=leaks.txt --leak-check=full --show-reachable=yes --show-leak-kinds=all --track-origins=yes ./$(NAME)


debug : fclean
	@echo "				$(_BG_CYAN)BUGS SCAN$(_END)"
	@scan-build-12 make -j

gitt: fclean
	@echo "\n"
	@echo "				$(_BG_CYAN)GIT FEATURES$(_END)\n"
	git add . 
	@echo "[$(_GREEN)!$(_END)] Adding files ... 	  [$(_BK_GREEN)SUCCESS$(_END)]"
	@echo "[$(_RED)!$(_END)] Committing ... 	  [$(_RED)  FAIL $(_END)]"
	@read -p "--> Need a name to commit (one word)&> " var
	git commit -m var
	@echo "[$(_GREEN)!$(_END)] Committing ... 	  [$(_BK_GREEN)SUCCESS$(_END)]\n"
	git push
	@echo "[$(_GREEN)!$(_END)] Pushing :		    [$(_BK_GREEN)SUCCESS$(_END)]\n"
	@bash .script_bar.sh
	@echo "--> Repo up to pull or merge"

.PHONY : all clean fclean re leak debug git
