
#include "../inc/builtin.h"

int exec_exit(char *str)
{
    char **split;
    int i;

    split = ft_split(str, ' ');
    if (split == NULL)
        return (-1);
    if (ft_strncmp(split[0], "exit", ft_strlen(split[0])) != 0)
		return (-1);
    else
        ft_putstr_fd("exit\n", 2);
    i = 0;
    while (split[i])
        i++;
    if (i > 2)
		return (ft_err_print( "exit", NULL, "too many arguments"));
    exit(1);
    return(1);
}