# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: almaz <almaz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 12:33:55 by bbrusco           #+#    #+#              #
#    Updated: 2022/07/23 13:59:38 by almaz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ./minishell

CC			= cc
C_FLAGS		= -Wall -Werror -Wextra
LDLIBS		= -lreadline
LIBDIR		= ./libft
LIBFT_NAME	= $(LIBDIR)/libft.a
RM			= rm -rf

SDIR		= src
ODIR		= obj

HEADER		= minishell.h
SRC			= main.c parse_errors.c \
				parse_utils.c parse_zone.c remove_quotes.c \
				special_character.c executing.c

SRCS		= $(SRC)
OBJS		= $(addprefix $(ODIR)/, $(SRCS:.c=.o))

LDLIBS		:= $(addprefix -L./, $(LIBDIRS)) $(LDLIBS)
INCLUDES	:= -I./inc/ $(addprefix -I./, $(LIBDIRS)) \
			   $(addprefix -I./, $(addsuffix /inc, $(LIBDIRS)))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): 	$(OBJS)
	@make -C $(LIBDIR) all
	@$(CC) $(C_FLAGS) $(OBJS) $(LDLIBS) $(LIBFT_NAME) -o $(NAME)
	@echo "\n-- $(NAME) created \n"

$(ODIR)/%.o: $(SDIR)/%.c
	@mkdir -p $(dir $@)
	@${CC} ${C_FLAGS} -c -o $@ $< $(INCLUDES)

clean:
	@make -C $(LIBDIR) clean
	@${RM} ${ODIR}
	@echo "\n-- deleting objects\n"

fclean:		clean
	@make -C $(LIBDIR) fclean
	@${RM} ${NAME}
	@echo "-- deleting executable\n"

re:			fclean all