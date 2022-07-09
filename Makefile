# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrusco <bbrusco@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 12:33:55 by bbrusco           #+#    #+#              #
#    Updated: 2022/07/09 15:43:37 by bbrusco          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ./minishell

CC			= gcc
C_FLAGS		= -Wall -Werror -Wextra
L_FLAGS		= -lreadline
LIBDIR		= ./libft
LIBFT_NAME	= $(LIBDIR)/libft.a
RM			= rm -f

HEADER		= minishell.h env.h
SRC			= free.c err.c utils.c main.c
SRCS_ENV	= env.c
SRCS		= $(SRC) $(SRCS_ENV)
OBJS		= $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): 	$(OBJS) ${HEADER}
	@make -C $(LIBDIR) all
	@$(CC) $(C_FLAGS) $(SRCS) $(L_FLAGS) $(LIBFT_NAME) -o $(NAME)
	@echo "\n-- $(NAME) created \n"

%.o :		%.c ${HEADER}
	@${CC} ${C_FLAGS} -c -o $@ $<

clean:
	@make -C $(LIBDIR) clean
	@${RM} ${OBJS}
	@echo "\n-- deleting objects\n"

fclean:		clean
	@make -C $(LIBDIR) fclean
	@${RM} ${NAME}
	@echo "-- deleting executable\n"

re:			fclean all