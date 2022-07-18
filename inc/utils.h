
#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void	*ft_free_split(char **split);
void    ft_free_all(void);

int     print_error_errno(char *s1, char *s2);
int     ft_err_print(char *s1, char *s2, char *err_log);

int     split_count(char **split);
int     env_rm_value(char ***split, char *key);
int     env_replace_value(char ***split, char *old_str, char *new_str);
int     env_add_value(char ***split, char *new_str);

#endif