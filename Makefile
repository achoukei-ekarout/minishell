NAME = minishell
# -fsanitize=address
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I includes

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC =  main.c $(wildcard src/built_ins/*.c) $(wildcard src/execusion/*.c) $(wildcard src/helpers/*.c) $(wildcard src/parse/*.c) $(wildcard src/errors/*.c)

OBJ = $(SRC:.c=.o)

RM = rm -f

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR) bonus

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline $(LIBFT) -o $(NAME)

clean:
	$(RM) $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

valgrind:
	valgrind --leak-check=full --show-leak-kinds=definite ./$(NAME)

debug:
	gdb -tui ./$(NAME)

re: fclean all

.PHONY: all clean fclean valgrind debug re
