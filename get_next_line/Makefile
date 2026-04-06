# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekarout <ekarout@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/31 20:39:54 by ekarout           #+#    #+#              #
#    Updated: 2026/04/06 11:30:20 by ekarout          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -I includes

RM = rm -f

AR = ar rcs

SRC = get_next_line.c get_next_line_utils.c add_history.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)
      
%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@
      
clean: 
	$(RM) $(OBJ)
      
fclean: clean
	$(RM) $(NAME)
      
re: fclean all

.PHONY: all clean fclean re
