# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epinaud <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/25 16:30:14 by epinaud           #+#    #+#              #
#    Updated: 2024/10/02 20:58:13 by epinaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FILES = server.c
  
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

OBJ_ALL = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

LIBFT = libft/libft.a

CFLAGS = -Wall -Wextra -Werror -I.

NAME = server.a

OBJ_DIR = .obj

CC = cc

$(OBJ_DIR)/%.o : %.c
	@$(CC) -D_XOPEN_SOURCE=700 -c $(CFLAGS) -o $@ $<

all: libft server

libft :
	@git -C libft pull
	@make -C libft

relibft:
	@git -C libft pull
	@make re -C libft

$(NAME): $(OBJ_DIR) $(OBJ)
	ar rcs $(NAME) $(OBJ)

server: $(NAME) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^

.obj:
	@mkdir -p .obj

clean:
	@rm -f $(OBJ_ALL)
	@make clean -C libft

fclean:  clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@make fclean -C libft

re: fclean relibft server

.PHONY:  all clean fclean re bonus libft relibft
