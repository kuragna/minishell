NAME	   = minishell
CC		   = gcc
CFLAGS	   = -Wall -Werror -Wextra
RM		   = rm -f

SRC		   = main.c 

SRC			:= $(addprefix src/, $(SRC))

OBJ			= $(SRC:.c=.o)

all: $(NAME) 

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(OBJ) 
	$(CC) -o $@ $(CFLAGS) $<
clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
