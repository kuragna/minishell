NAME	   = minishell
CC		   = gcc
CFLAGS	   = -Wall -Werror -Wextra -g3 #-fsanitize=address

LDLIBFT		= ./libft
RL			= /Users/${USER}/.brew/opt/readline/ 

LDFLAGS		= -L$(LDLIBFT) -L$(addsuffix lib, $(RL)) -I$(addsuffix include, $(RL)) -lft -lreadline
RM		   = rm -f
SRC		   = main.c ms_builtins.c 
SRC			:= $(addprefix src/, $(SRC))

OBJ			= $(SRC:.c=.o)


all: $(NAME)

libft: 
	make -C ./libft

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
$(NAME): libft $(OBJ)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(OBJ)
clean:
	make clean -C ./libft
	$(RM) $(OBJ)

fclean: clean
	make fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re libft test
