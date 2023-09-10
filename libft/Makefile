# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 12:33:39 by kbouzegh          #+#    #+#              #
#    Updated: 2023/08/29 23:39:48 by ayael-ou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = ./srcs/
SRCS = ft_strlen.c\
	   ft_isalpha.c\
	   ft_isalnum.c\
	   ft_isascii.c\
	   ft_isdigit.c\
	   ft_isprint.c\
	   ft_memset.c\
	   ft_bzero.c\
	   ft_memcpy.c\
	   ft_memmove.c\
	   ft_strlcpy.c\
	   ft_strlcat.c\
	   ft_toupper.c\
	   ft_tolower.c\
	   ft_strchr.c\
	   ft_strrchr.c\
	   ft_memchr.c\
	   ft_memcmp.c\
	   ft_strnstr.c\
	   ft_atoi.c\
	   ft_calloc.c\
	   ft_strdup.c\
	   ft_substr.c\
	   ft_strjoin.c\
	   ft_strjoin_all.c\
	   ft_strcalle.c\
	   ft_strtrim.c\
	   ft_split.c\
	   ft_itoa.c\
	   ft_strmapi.c\
	   ft_striteri.c\
	   ft_putchar_fd.c\
	   ft_putstr_fd.c\
	   ft_putendl_fd.c\
	   ft_putnbr_fd.c\
	   ft_strncmp_pipex.c\
	   ft_strncmp.c\
	   ft_split_pip.c\
	   ft_print_fd.c\

SBONUS = ft_lstnew.c\
		 ft_lstadd_front.c\
		 ft_lstsize.c\
		 ft_lstlast.c\
		 ft_lstadd_back.c\
		 ft_lstdelone.c\
		 ft_lstclear.c\
		 ft_lstiter.c\
		 ft_lstmap.c
OBJS = ${SRCS:.c=.o}
BONUSOBJ = ${SBONUS:.c=.o}
NAME = libft.a
CC = gcc
RM = rm -f
.c.o:
	${CC} -Wall -Wextra -Werror -c $< -o ${<:.c=.o}
${NAME}: ${OBJS}
	ar rc ${NAME} ${OBJS}
all : ${NAME}
bonus : ${BONUSOBJ} ${OBJS}
	ar rc ${NAME} ${BONUSOBJ}
clean :
	${RM} ${OBJS} ${BONUSOBJ} ${DEPS}
fclean : clean
	${RM} ${NAME}
so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJS)
re : fclean all bonus
.PHONY : all clean fclean re
