NAME = minishell
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I includes

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC =  main.c src/built_ins/environ.c src/built_ins/ft_cd.c src/built_ins/ft_env.c src/built_ins/ft_export.c \
	   src/built_ins/ft_unset.c src/built_ins/environ_mehods.c src/built_ins/ft_cd_helper.c \
	   src/built_ins/ft_exit.c src/built_ins/ft_export_utils.c src/built_ins/environ_utils.c \
	   src/built_ins/ft_echo.c src/built_ins/ft_export_all.c src/built_ins/ft_pwd.c \
	   src/execution/execute.c src/execution/execute_utils.c src/execution/heredoc.c \
	   src/execution/heredoc_readline.c src/execution/process_helpers.c src/execution/redirections.c \
	   src/helpers/garbage_collector.c src/helpers/libft_allocate.c src/helpers/libft_allocate_cont.c \
	   src/helpers/ft_split_set.c src/helpers/signals.c src/helpers/signals_helpers.c src/parse/expand_heredoc.c \
	   src/parse/expansion_helper.c src/parse/parse.c src/parse/syntax.c src/parse/token_utils.c \
	   src/parse/expansion.c src/parse/expansion_tokens.c src/parse/parse_utils.c src/parse/token_get_index.c \
	   src/parse/tree_nodes.c src/parse/expansion_counter.c src/parse/heredoc_line_expansion.c \
	   src/parse/redirect.c src/parse/tokenize.c src/parse/utils.c src/errors/built_ins_errors.c \
	   src/errors/parse.errors.c

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

re: fclean all

.PHONY: all clean fclean re
