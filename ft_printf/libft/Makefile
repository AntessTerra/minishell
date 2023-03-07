# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MAKEFILE                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbartosi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 15:50:12 by jbartosi          #+#    #+#              #
#    Updated: 2023/01/09 15:50:14 by jbartosi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_atoi.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memset.c ft_memcpy.c ft_bzero.c ft_memcmp.c ft_memchr.c ft_memmove.c ft_strdup.c ft_strlen.c ft_strjoin.c ft_strlcpy.c ft_strlcat.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strnstr.c ft_calloc.c ft_strmapi.c ft_striteri.c ft_substr.c ft_strtrim.c ft_split.c

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	ar -cr $(NAME) $(OBJS)

%.o: %.c
	cc $(CFLAGS) -c $(SRCS) $(BONUS)

bonus: bbonus

bbonus: $(NAME)
	ar r $(NAME) $(BONUS_OBJS)

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY:
	all clean fclean re bonus
