# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/03 12:50:33 by glacroix          #+#    #+#              #
#    Updated: 2023/10/09 14:51:02 by glacroix         ###   ########.fr        #
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
NAME = libft.a

#SRC & OBJS Details
# **************************************************************************** #
SRCS 	=  srcs/ft_bzero.c\
		srcs/ft_isalnum.c\
        srcs/ft_isnumber.c\
		srcs/ft_isalpha.c\
        srcs/ft_isascii.c\
        srcs/ft_isdigit.c\
        srcs/ft_isprint.c\
        srcs/ft_memcpy.c\
        srcs/ft_memmove.c\
        srcs/ft_memset.c\
        srcs/ft_strchr.c\
        srcs/ft_strlcat.c\
        srcs/ft_strlcpy.c\
        srcs/ft_strlen.c\
		srcs/ft_strncmp.c\
        srcs/ft_strrchr.c\
        srcs/ft_tolower.c\
		srcs/ft_toupper.c\
		srcs/ft_memchr.c\
		srcs/ft_memcmp.c\
		srcs/ft_strnstr.c\
		srcs/ft_calloc.c\
		srcs/ft_strdup.c\
		srcs/ft_atoi.c\
		srcs/ft_substr.c\
		srcs/ft_strjoin.c\
		srcs/ft_strtrim.c\
		srcs/ft_split.c\
		srcs/ft_itoa.c\
		srcs/ft_strmapi.c\
		srcs/ft_striteri.c\
		srcs/ft_putchar_fd.c\
		srcs/ft_putstr_fd.c\
		srcs/ft_putendl_fd.c\
		srcs/ft_putnbr_fd.c\
       	srcs/ft_lstnew_bonus.c\
		srcs/ft_lstadd_front_bonus.c\
		srcs/ft_lstsize_bonus.c\
		srcs/ft_lstlast_bonus.c\
		srcs/ft_lstadd_back_bonus.c\
		srcs/ft_lstdelone_bonus.c\
		srcs/ft_lstclear_bonus.c\
		srcs/ft_lstiter_bonus.c\
		srcs/ft_lstmap_bonus.c\
		srcs/ft_pointer.c\
		srcs/ft_pow.c\
		srcs/ft_printf.c\
   		srcs/ft_putchar.c\
		srcs/ft_putnbr.c\
   		srcs/ft_putnbr_hex.c\
	   	srcs/ft_putnbr_uns.c\
	   	srcs/ft_putstr.c\
		srcs/get_next_line_utils_bonus.c\
		srcs/get_next_line_bonus.c\
		srcs/ft_isspace.c\
 
OBJS 	= $(SRCS:%.c=objs/%.o)

#Execution
# **************************************************************************** #
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra #-g -fsanitize=address

#SRC Execution
# **************************************************************************** #
$(NAME): objs $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@echo $(GREEN) "\n         Libft Compiled!       \n" $(RESET)

#Makefile Cmds
# **************************************************************************** #
objs:
	@mkdir -p objs/srcs

objs/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	@rm -rf objs

fclean: clean
	@rm -f $(NAME)

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re re_bonus bonus
