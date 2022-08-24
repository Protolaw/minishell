
#include "builtin.h"

// int get_exit_status(void)
// {

// }

int	is_numeric(char *str)
{
	int i;

	i = 0;
	if (!str[0])
		return (ft_err_print("exit", str, "numeric argument required"));
	else if ((str[0] == '-' || str[0] == '+') && str[1] != '\0')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (ft_err_print("exit", str, "numeric argument required"));
		i++;
	}
	return (1);
}

int handle_exit(char **split, int exit_num)
{
	int i;

	i = 0;
	// exit_num = get_exit_status();
	while (split[i])
		i++;
	if (i >= 2 && is_numeric(split[1]) != 1)
		exit_num = 255;
	else if (i == 2)
	{
		exit_num = ft_atoi(split[1]);
		if (exit_num > 255 || exit_num < -255) // https://tldp.org/LDP/abs/html/exitcodes.html
			exit_num = exit_num % 256;
		if (exit_num < 0)
			exit_num = 256 + exit_num;
	}
    else if (i > 2)
		return (ft_err_print("exit", NULL, "too many arguments"));
	return (exit_num);
}

int	exec_exit(char **cmd)
{
	int	exit_num;

	ft_putstr_fd("exit\n", 2);
	exit_num = 0;
	exit_num = handle_exit(cmd, exit_num);
    if (exit_num == -1)
	{
		ft_free_split(cmd);
		return (-1);
	}
	ft_free_all();
	// printf("%d\n", exit_num); // Доделать статус выхода для ошибки с $?
    exit(exit_num);
}