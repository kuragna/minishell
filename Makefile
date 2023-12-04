# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabourri <aabourri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/09 14:16:51 by glacroix          #+#    #+#              #
#    Updated: 2023/12/04 14:39:31 by aabourri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Colors
# **************************************************************************** #
RESET  		= "\x1B[0m"
RED  		= "\x1B[31m"
GREEN  		= "\x1B[32m"
YELLOW  	= "\x1B[33m"
BLUE 		= "\x1B[34m"
MAGENTA 	= "\x1B[35m"
CAYN  		= "\x1B[36m"
WHITE  		= "\x1B[37m"

#Program name
# **************************************************************************** #
NAME	   = minishell

#SRC & OBJS Details
# **************************************************************************** #

SRCS		=	ms_malloc.c \
				ms_ast_destroy.c \
				ms_signal.c \
				ms_cmd_utils.c \
				builtins/ms_env.c \
				builtins/ms_env_utils.c \
				ms_utils.c \
				ms_error.c \
				ms_io_handle.c \
				ms_lexer.c \
				ms_parser.c \
				ms_parser_utils.c \
				ms_exec.c \
				main.c \
				ms_envcpy.c \
				ms_get_lexeme.c \
				ms_lexeme_utils.c \
				builtins/ms_exit.c \
				builtins/ms_unset.c \
				builtins/ms_echo.c \
				builtins/ms_pwd.c \
				builtins/ms_cd.c \
				builtins/ms_export.c 

OBJ			= $(SRCS:%.c=objs/%.o)
SRCS		:= $(addprefix src/, $(SRCS))


#Routes
# **************************************************************************** #
LDLIBFT		= ./libft
RL			= /Users/${USER}/.brew/opt/readline/ 

#Execution
# **************************************************************************** #
CC		   = gcc
CFLAGS	   = -Wall -Werror -Wextra -g3 -fsanitize=address
LDFLAGS    = -L$(LDLIBFT) -L$(addsuffix lib, $(RL)) 
LDFLAGS    += -I$(addsuffix include, $(RL)) -lft -lreadline
RM		   = rm -rf 


#SRC Execution
# **************************************************************************** #
$(NAME): libft objs $(OBJ)
	@$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(OBJ)
	@echo $(MAGENTA) "\n         Minishell Compiled!       \n" $(RESET)

#Makefile Cmds
# **************************************************************************** #
all: $(NAME)

libft: 
	@make -C ./libft

objs/%.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@

objs: 
	@mkdir -p objs/src
	@mkdir -p objs/src/builtins

clean:
	@make clean -C ./libft
	@$(RM) objs

fclean: clean
	@make fclean -C ./libft
	@$(RM) $(NAME)
	@echo $(RED) "\n >>>>>>>> Deleted all *.o and *.a! <<<<<<<< \n" $(RESET)

re: fclean all


.PHONY: all clean fclean re libft
