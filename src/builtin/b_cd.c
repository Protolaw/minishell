
#include "builtin.h"

int	update_pwd(void) // Обновление значение PWD и OLDPWD в envcar
{
	char *buf;

	buf = NULL;
	if (get_value_env("PWD"))
	{
		if (env_set_var("OLDPWD", get_value_env("PWD")) == -1) // Swap the values
			return (-1);
	}
	else
		env_unset_var("OLDPWD"); 		// If value PWD not defined delete the value OLDPWD
	buf = getcwd(buf, 0);
	if (buf == NULL)
		return (print_err_errno("cd", NULL));
	if (env_set_var("PWD", buf) == -1)
	{
		ft_free_str(&buf);
		return (-1);
	}
	ft_free_str(&buf);
	return (0);
}

char	*get_dir(int argc, char **argv)
{
	char	*dir;

	dir = NULL;
	if (argc == 1 || (argv[1] && ft_strncmp(argv[1], "~", 2) == 0))
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

int cd_handle(int i, char *dir, char **split)
{
	if (i > 2)
		return (ft_err_print("cd", NULL, "too many arguments"));
    if (dir == NULL)
		return (-1);
    if (chdir(dir) == -1)
		return (print_err_errno("cd", dir)); // No such file or directory
	if (split[1] && ft_strncmp(split[1], "-", 1) == 0)
		ft_putendl_fd(dir, 1);
    if (update_pwd() == 1)
		return (-1);
	return (0);
}

int exec_cd(char **cmd)
{
    int i;
    char *dir;
	// char *tmp;

	i = 0;
    dir = get_dir(i, cmd);
	// tmp = get_dir(i, split);
	// dir = ft_strtrim(tmp, "/");
	if (cd_handle(i, dir, cmd) == -1)
	{
		ft_free_split(cmd);
		return (-1);
	}
	ft_free_split(cmd);
    return (0);
}
