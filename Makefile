# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epinaud <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/25 16:30:14 by epinaud           #+#    #+#              #
#    Updated: 2024/09/23 12:22:39 by epinaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PRINTF_FILES = ft_printf.c \
		ft_print_argument.c \
		ft_parse_directives.c \
		ft_print_directives.c \

LIB_FILES = ft_strlen.c \
			ft_nbrlen.c \
			ft_nbrblen.c \
			ft_count_digits.c \
			ft_strchr.c \
			ft_isdigit.c \
			ft_putchar_fd.c \
			ft_itoa_base.c \
			ft_putstr_fd.c \
			ft_putnbr_fd.c \
			ft_putnbr_base_fd.c \
			ft_base_integrity.c \
			ft_check_dup.c \
			ft_min_max.c \

OBJ_DIR = .obj

ft_printf_OBJ = $(PRINTF_FILES:.c=.o)

LIB_OBJ = $(LIB_FILES:.c=.o)

LIBBJALL = $(addprefix $(OBJ_DIR)/, $(ft_printf_OBJ) $(LIB_OBJ))

CFLAGS = -Wall -Wextra -Werror

NAME = ft_printf.a

CLIENT = client

SERVER = server

all: $(CLIENT) $(SERVER)

$(OBJ_DIR)/%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(NAME): $(OBJ_DIR) $(OBJALL)
	ar rcs $(NAME) $(OBJALL)

bonus: $(NAME)

.obj:
	mkdir -p .obj

clean:
	rm -f $(OBJALL)

fclean:  clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)

re: fclean $(NAME)

.PHONY:  all clean fclean re bonus
