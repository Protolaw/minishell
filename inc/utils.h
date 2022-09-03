
#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void	ft_free_str(char **str);
void	*ft_free_split(char **split);
void    ft_free_all(void);
char	*ft_empty(char *s1);

int     print_err_errno(char *s1, char *s2);
int     ft_err_print(char *s1, char *s2, char *err_log);

int     split_count(char **split);
void	split_sort(char **split);

int     env_rm_value(char ***split, char *key);
int     env_replace_value(char ***split, char *old_str, char *new_str);
int     env_add_value(char ***split, char *new_str);

char	*no_quotes(char *s);
int     check_quotes(char *s);

char	*str_append(char *s1, char *s2);
char	*chr_append(char *str, char chr);
int     split_replace_str(char ***split, char *old_str, char *new_str);

#endif