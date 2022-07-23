
#ifndef ENV_H
# define ENV_H

# include "minishell.h"

int     env_is_var_char(char c);
int		ft_init_env();
char	*get_value_env(char *key);
char	*env_find_var(char *key);

int     env_unset_var(char *name);
int     env_put_var(char *str);
int     env_set_var(char *name, char *value);
int     env_var_is_value(char *var_name, char *value);

#endif