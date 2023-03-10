# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 13:56:55 by jbartosi          #+#    #+#              #
#    Updated: 2023/03/10 15:05:36 by jbartosi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Wextra -Werror
PRINTF = ft_printf
LIBFT = ft_printf/libft

SRC = minishell.c prompt.c commands.c split_utils.c
OBJ = $(SRC:.c=.o)

all: lib $(NAME)

lib:
	@make -C $(PRINTF)
	@echo "Finished making libraries :D"

%.o: %.c
	@cc -g -c $<

$(NAME): $(OBJ)
	@cc $(CFLAGS) -L $(PRINTF) -o $@ $^ -lreadline -lftprintf

clean:
	@rm -f $(OBJ)
	@make clean -C $(PRINTF)

fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@make fclean -C $(PRINTF)

re:	fclean
	@make all

.PHONY: re, fclean, clean
