# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: almaz <almaz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 12:33:55 by bbrusco           #+#    #+#              #
#    Updated: 2022/09/21 16:06:33 by almaz            ###   ########.fr        #
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
SRC			= main.c 
SRC_PARSE	= parse_errors.c parse_utils.c parse_zone.c parse_cases.c
SRC_LEX		= remove_quotes.c special_character.c check_pipe.c
SRC_EXEC	= executing.c exec_exit.c redir.c path_cmd.c exec_utils.c no_pipe.c
SRC_UTILS	= free.c err.c utils.c ut_str.c
SRC_ENV		= env_edit.c env.c
SRC_EXPAND	= expand.c #here_doc.c
SRC_BLTIN	= builtin.c b_env.c b_cd.c b_pwd.c b_exit.c b_echo.c b_export.c b_unset.c

SRCS_PARSE	= $(addprefix parser/, $(SRC_PARSE))
SRCS_LEX	= $(addprefix lexer/, $(SRC_LEX))
SRCS_EXEC	= $(addprefix exec/, $(SRC_EXEC))
SRCS_UTILS	= $(addprefix utils/, $(SRC_UTILS))
SRCS_BLTIN	= $(addprefix builtin/, $(SRC_BLTIN))
SRCS_ENV	= $(addprefix env/, $(SRC_ENV))
SRCS_EXPAND	= $(addprefix expand/, $(SRC_EXPAND))
SRCS		= $(SRC) $(SRCS_ENV) $(SRCS_BLTIN) $(SRCS_PARSE) $(SRCS_LEX) $(SRCS_EXPAND) $(SRCS_EXEC) $(SRCS_UTILS)
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