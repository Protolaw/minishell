#include "exec.h"

char	*path_combine(char **path, char *cmd)
{
	char	*dir;
	char	*full_dir;
	int		i;

	i = -1;
	while (path[++i])
	{
		dir = ft_strjoin(path[i], "/");
		if (!dir)
			return (NULL);
		full_dir = ft_strjoin(dir, cmd);
		if (!full_dir)
		{
			free(dir);
			return (NULL);
		}
		free(dir);
		if (access(full_dir, F_OK) < 0)
			free(full_dir);
		else
			return (full_dir);
	}
	return (NULL);
}

char	*get_path(char *cmd)
{
	char	**path;
	char	*fullpath;

	path = ft_split(get_value_env("PATH"), ':');
	if (!path)
		return (NULL);
	fullpath = path_combine(path, cmd);
	ft_free_split(path);
	return (fullpath);
}

char *joining_cmd(char *str, char *app)
{
	char	*space;
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_empty(str);
	tmp2 = ft_strjoin(tmp1, app);
	space = ft_strdup(" ");
	str = ft_strjoin(tmp2, space);
	free(space);
	free(tmp1);
	free(tmp2);
	return(str);
}

char	**get_cmd(char **argv, t_pipex *p)
{
	int 	i;
	char	**cmd;
	char	*str;

	i = 0;
	str = NULL;
	while (argv[i])
	{
		if (argv[i][0] == '|' && argv[i][1] == '\0')
			break ;
		if (check_red(argv[i]))
		{
			if (redirection_case(argv, &i, p))
				break ;
		}
		else
			str = joining_cmd(str, argv[i]);
		i++;
	}
	cmd = ft_split(str, ' ');
	free(str);
	return (cmd);
}

int do_cmd(char **cmd, int status)
{
	char *path;

	path = get_path(cmd[0]);
	if (!path)
	{
		ft_err_print(cmd[0], NULL, "command not found");
		return (EXEC_NOTFOUND);
	}
	else
		execve(path, cmd, g_env);
	if (errno == ENOENT)
		status = EXEC_NOTFOUND;
	else
		status = EXEC_NOEXEC;
	print_err_errno(cmd[0], NULL);
	free(path);
	return (status);
}