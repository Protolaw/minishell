#include "expand.h"

int	exp_env_var(char **dest, char *var)
{
	char	*var_name;
	char	*var_value;
	int		i;

	var_name = ft_strdup("");
	if (var_name == NULL)
		return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
	i = 1;
	while (env_is_var_char(var[i]))
	{
		var_name = chr_append(var_name, var[i]);
		if (var_name == NULL)
			return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
		i++;
	}
	var_value = get_value_env(var_name);
	free(var_name);
	if (var_value == NULL)
		var_value = "";
	*dest = str_append(*dest, var_value);
	if (*dest == NULL)
		return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
	return (SUCCESS);
}

int	exp_exit_code(char **dest)
{
	char	*exit_str;

	exit_str = ft_itoa(get_exit_status());
	if (exit_str == NULL)
		return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
	*dest = str_append(*dest, exit_str);
	free(exit_str);
	if (*dest == NULL)
		return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
	return (SUCCESS);
}

int	get_exp(char *elem, char **dest, int *i)
{
	if (elem[*i] == '$' && elem[*i + 1] == '?')
	{
		if (exp_exit_code(dest) != SUCCESS)
			return (FAILURE);
		(*i)++;
	}
	else if (elem[*i] == '$' && (env_is_var_char(elem[*i + 1])))
	{
		if (exp_env_var(dest, &(elem[*i])) != SUCCESS)
			return (FAILURE);
		while (env_is_var_char(elem[*i + 1]))
			(*i)++;
	}
	else
		*dest = chr_append(*dest, elem[*i]);
	if (*dest == NULL)
		return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
	return (SUCCESS);
}

int expand_elem(char *elem, char ***cmd)
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
	split_replace_str(cmd, elem, dest);
    return (SUCCESS);
}

int expand_list(char **cmd)
{
    int i;

    i = -1;
    while (cmd[++i])
    {
        if (expand_elem(cmd[i], &cmd) != SUCCESS)
			return (FAILURE);
    }
    return (SUCCESS);
}

int	handle_expand(char **cmd)
{
	int		status;

	status = expand_list(cmd);
    return (status);
}