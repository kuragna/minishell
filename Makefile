NAME	   = minishell
CC		   = gcc
CFLAGS	   = -Wall -Werror -Wextra -fsanitize=thread
LDFLAGS    = -L./libft -lft -lreadline
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

.PHONY: all clean fclean re libft
