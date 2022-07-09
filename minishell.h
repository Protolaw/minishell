#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>

# include "env.h"
# include "libft/libft.h"

# define CLOSE "\001\033[0m\002"
# define BLOD "\001\033[1m\002"
# define BEGIN(x,y) "\001\033["#x";"#y"m\002"

# define SHELL_NAME "minishell"

void	*ft_free_split(char **split);
int     split_count(char **split);
int     ft_err_print(char *s);

#endif