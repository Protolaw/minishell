#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

int     ft_print_env(char **env);
int     exec_cd(char **cmd);
int     exec_pwd(void);
int     exec_exit(char **cmd);
int     exec_echo(char **cmd);
int     exec_export(char **cmd);
int		exec_unset(char **cmd);
int     ft_isbuiltin(char **cmd);

#endif