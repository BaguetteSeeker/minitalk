# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epinaud <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/25 16:30:14 by epinaud           #+#    #+#              #
#    Updated: 2024/10/14 01:41:46 by epinaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRV_SRC = server.c minitalk_utils.c

SRV_OBJ = $(addprefix $(OBJ_DIR)/, $(SRV_SRC:.c=.o))

CLNT_SRC = client.c minitalk_utils.c
  
CLNT_OBJ =$(addprefix $(OBJ_DIR)/, $(CLNT_SRC:.c=.o))

LIBFT = libft/libft.a

CFLAGS = -Wall -Wextra -Werror -I.

SRV_NAME = server.a

CLNT_NAME = client.a

OBJ_DIR = .obj

CC = cc -D_XOPEN_SOURCE=700 

$(OBJ_DIR)/%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

all: libft server client

$(SRV_NAME): $(OBJ_DIR) $(SRV_OBJ)
	ar rcs $(SRV_NAME) $(SRV_OBJ)

$(CLNT_NAME): $(OBJ_DIR) $(CLNT_OBJ)
	ar rcs $(CLNT_NAME) $(CLNT_OBJ)

server: $(SRV_NAME) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^

client: $(CLNT_NAME) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^

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
	@rm -f $(SRV_NAME) $(CLNT_NAME)
	@rm -rf $(OBJ_DIR)
	@make fclean -C libft

re: fclean relibft server client

.PHONY:  all clean fclean re bonus libft relibft
