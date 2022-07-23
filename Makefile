# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: almaz <almaz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 12:33:55 by bbrusco           #+#    #+#              #
#    Updated: 2022/07/23 12:17:42 by almaz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ./minishell

CC			= gcc
C_FLAGS		= -Wall -Werror -Wextra
LDLIBS		= -lreadline
LIBDIR		= ./libft
LIBFT_NAME	= $(LIBDIR)/libft.a
RM			= rm -rf

SDIR		= src
ODIR		= obj

HEADER		= minishell.h env.h builtin.h utils.h
SRC			= free.c err.c utils.c main.c
SRC_ENV		= env.c env_edit.c
SRC_BLTIN	= b_env.c b_cd.c b_pwd.c b_exit.c b_echo.c b_export.c b_unset.c
SRCS_BLTIN	= $(addprefix builtin/, $(SRC_BLTIN))
SRCS		= $(SRC) $(SRC_ENV) $(SRCS_BLTIN)
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