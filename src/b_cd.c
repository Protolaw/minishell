
#include "../inc/builtin.h"

int	update_pwd(void) // Обновление значение PWD и OLDPWD в envcar
{
	char	buf[1000];

	if (get_value_env("PWD"))
	{
		if (env_set_env("OLDPWD", get_value_env("PWD")) == -1) // Swap the values
			return (-1);
	}
	else
		env_unset_var("OLDPWD"); 		// If value PWD not defined delete the value OLDPWD
	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		print_error_errno("cd", NULL);
		return (-1);
	}
	if (env_set_env("PWD", buf) == -1)
		return (-1);
	return (0);
}

char	*get_dir(int argc, char **argv)
{
	char	*dir;

	dir = NULL;
	if (argc == 1)
	{
		dir = get_value_env("HOME");
		if (dir == NULL)
            ft_err_print("cd", NULL, "HOME not set"); // by manual
	}
	else if (argv[1] && ft_strncmp(argv[1], "-", 2) == 0)
	{
		dir = get_value_env("OLDPWD");
		if (dir == NULL)
            ft_err_print("cd", NULL, "OLDPWD not set"); // for cmd "cd -"
	}
	else
		dir = argv[1];
	return (dir);
}

int exec_cd(char *str)
{
    char **split;
    int i;
    char *dir;

    split = ft_split(str, ' ');
    i = 0;
    while(split[i])
        i++;
    dir = get_dir(i, split);
    if (dir == NULL)
		return (-1);
    if (chdir(dir) == -1)
		return (print_error_errno("cd", dir)); // No such file or directory
    if (update_pwd() == 1)
		return (-1);
    return (0);
}
