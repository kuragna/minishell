# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabourri <aabourri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/09 14:16:51 by glacroix          #+#    #+#              #
#    Updated: 2023/10/25 16:46:42 by aabourri         ###   ########.fr        #
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
SRCS		   = main.c \
				ms_signal.c \
				ms_utilts.c \
				builtins/ms_env_utilts.c \
				builtins/ms_export.c \
				builtins/ms_env.c \
				builtins/ms_exit.c \
				builtins/ms_unset.c \
				builtins/ms_echo.c \
				builtins/ms_pwd.c \
				builtins/ms_cd.c \
				


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

test:
	@echo $(OBJ)

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
