# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrusco <bbrusco@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/29 11:53:47 by bbrusco           #+#    #+#              #
#    Updated: 2022/07/09 15:26:26 by bbrusco          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
NAME		=	libft.a
AR			=	ar
HEADER		=	libft.h
CFLAGS		=	-Wall -Wextra -Werror
ARFLAGS		=	rc
SRCS		=	ft_atoi.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strncmp.c \
				ft_strdup.c \
				ft_tolower.c \
				ft_memcmp.c \
				ft_memset.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memchr.c \
				ft_calloc.c \
				ft_bzero.c \
				ft_toupper.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strchr.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_itoa.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_split.c \
			
BONUS		=	ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c 
			
OBJS		=	${SRCS:.c=.o}

BONUS_OBJS	=	${BONUS:.c=.o}
RM			=	rm -rf

all: ${NAME}

.c.o:	${HEADER}
	@${CC} ${CFLAGS} -c $*.c  -o $*.o

${NAME} : ${OBJS}
	@${AR} ${ARFLAGS} ${NAME} ${OBJS}
	@ranlib $(NAME)

bonus :	${OBJS} ${BONUS_OBJS}
		${AR} ${ARFLAGS} ${NAME} ${OBJS} ${BONUS_OBJS}
		ranlib $(NAME)

clean :
	@${RM} ${OBJS} ${BONUS_OBJS}

fclean : clean
	@${RM} ${NAME}

re : fclean all

.PHONY: all clean re