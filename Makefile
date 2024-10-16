# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epinaud <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/25 16:30:14 by epinaud           #+#    #+#              #
#    Updated: 2024/10/16 13:54:37 by epinaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE = server client

LDLIBS = libft/libft.a

CFLAGS = -Wall -Wextra -Werror -I.

OBJ_DIR = .obj

CC = cc -D_XOPEN_SOURCE=700 

$(OBJ_DIR)/%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: libft $(EXE)

server : server.o minitalk_utils.o

client : server.o minitalk_utils.o

$(EXE) :
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

libft :
	@git -C libft pull
	@make -C libft

relibft:
	@git -C libft pull
	@make re -C libft

.obj:
	@mkdir -p .obj

clean:
	@rm -f server client
	@make clean -C libft

fclean:  clean
	@rm -rf $(OBJ_DIR)
	@make fclean -C libft

re: fclean relibft server client

.PHONY:  all clean fclean re bonus libft relibft
