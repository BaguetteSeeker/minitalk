# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epinaud <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/25 16:30:14 by epinaud           #+#    #+#              #
#    Updated: 2024/10/17 14:28:27 by epinaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE = server client

LDLIBS = libft/libft.a

CFLAGS = -Wall -Wextra -Werror -I. -Ilibft/printf -ggdb3

OBJ_DIR = .obj

CC = cc -D_XOPEN_SOURCE=700

$(OBJ_DIR)/%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: libft $(OBJ_DIR) $(EXE)

$(EXE) :
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

server: .obj/server.o .obj/minitalk_utils.o

client: .obj/client.o .obj/minitalk_utils.o

libft:
	@git -C libft pull
	@make -C libft

relibft:
	@git -C libft pull
	@make re -C libft

.obj:
	mkdir -p .obj

clean:
	@rm -f $(EXE)
	@make clean -C libft

fclean:  clean
	@rm -rf $(OBJ_DIR)
	@make fclean -C libft

re: fclean relibft $(OBJ_DIR) $(EXE)

.PHONY:  all clean fclean re bonus libft relibft
