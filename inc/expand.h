#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

int		handle_expand(char **cmd);
int     expand_elem(char *elem, char ***cmd);
int     get_exp(char *elem, char **dest, int *i);

#endif