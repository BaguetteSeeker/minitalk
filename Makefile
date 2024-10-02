# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epinaud <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/25 16:30:14 by epinaud           #+#    #+#              #
#    Updated: 2024/10/02 17:16:35 by epinaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FILES = server.c
  
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

OBJ_ALL = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

LIBFT = libft/libft.a

CFLAGS = -Wall -Wextra -Werror -I.

NAME = server.a

OBJ_DIR = .obj

CC = cc -D_XOPEN_SOURCE=700

$(OBJ_DIR)/%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

all: server

$(NAME): $(OBJ_DIR) $(OBJ)
	ar rcs $(NAME) $(OBJ)

libft/libft.a:
	git -C libft pull
	-C libft make

server: $(NAME) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^

.obj:
	@mkdir -p .obj

clean:
	@rm -f $(OBJ_ALL)

fclean:  clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)

re: fclean server

.PHONY:  all clean fclean re bonus
