#include "expand.h"

static int	exp_exit_code(char **dest)
{
	char	*exit_str;

	exit_str = ft_itoa(get_exit_status());
	if (exit_str == NULL)
		return (ft_err_print(NULL, NULL, strerror(ENOMEM)));

	*dest = str_append(*dest, exit_str);
	free(exit_str);
	if (*dest == NULL)
		return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
	return (0);
}

int	get_exp(char *elem, char **dest, int *i)
{
	if (elem[*i] == '$' && elem[*i + 1] == '?')
	{
		if (exp_exit_code(dest) == FAILURE)
			return (FAILURE);
		(*i)++;
	}
	
	if (*dest == NULL)
		return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
	return (SUCCESS);
}

int expand_elem(char *elem)
{
    char *dest;
    int i;

    if (!elem || !ft_strchr(elem, '$'))
        return (SUCCESS);
    dest = ft_strdup("");
	if (dest == NULL)
		return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
    i = 0;
    while (elem[i])
    {
        if (get_exp(elem, &dest, &i) != SUCCESS)
		{
			free(dest);
			return (FAILURE);
		}
		i++;
    }
    free(elem);
    elem = dest;
    return (SUCCESS);
}

int expand_list(char **cmd)
{
    int i;

    i = -1;
    while (cmd[++i])
        if (expand_elem(cmd[i]) != SUCCESS)
			return (FAILURE);
    return (SUCCESS);
}

int	handle_expand(char **cmd)
{
	int		status;

	status = expand_list(cmd);
    // if (status != FAILURE)
	// 	status = expand_split(&cmd);
    return (status);
}