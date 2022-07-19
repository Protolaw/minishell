#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

int     ft_print_env(char **env);
int     exec_cd(char *str);
int     exec_pwd(void);
int     exec_exit(char *str);

#endif