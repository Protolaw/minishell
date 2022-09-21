#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

int     check_pipes(char *str, int *i);
int	quotes_counter(char *str, int *i, int count, char quote);


#endif