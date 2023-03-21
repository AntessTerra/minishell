# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbartosi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 12:24:34 by jbartosi          #+#    #+#              #
#    Updated: 2023/01/29 16:16:37 by jbartosi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_print_nbr.c ft_print_alpha.c ft_print_hex.c ft_printf.c ft_format.c
INC = ft_printf.h
OBJ = $(SRC:.c=.o)
NAME = libftprintf.a
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
LIBC = ar rc
LIBFT = ./libft/libft.a

.c.o:
	cc ${CFLAGS} -c $< -o ${<:.c=.o} -I ${INC}

${NAME}: ${OBJ}
	make -C ./libft
	cp ./libft/libft.a ${NAME}
	${LIBC} ${NAME} ${OBJ}

all: ${NAME}

bonus: all

clean:
	${MAKE} clean -C ./libft
	${RM} ${OBJ}
	${RM} ${OBJ_BONUS}

fclean:	clean
	${MAKE} fclean -C ./libft
	${RM} ${NAME}

re: fclean all
