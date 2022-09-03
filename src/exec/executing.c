#include "minishell.h"

static int	here_doc_check(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], "<<\0", 3) == 0)
			return (1);
		i++;
	}
	return (0);
}

static int	pipe_counter(char **argv)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while(argv[i])
	{
		if (ft_strncmp(argv[i], "|\0", 2) == 0)
			count++;
		i++;
	}
	return (count);	
}

static void close_pipe(t_pipex *p)
{
	close(p->pipefd[1]);
	if (p->close)
		close(p->close);
	p->std_in = p->pipefd[0];
	p->close = p->std_in;
}

static void	dupper(int fd1, int fd2)
{
	if (dup2(fd1, 0) == -1)
		exit(1);
	if (dup2(fd2, 1) == -1)
		exit(1);
}

static char	*path_combine(char **path, char *cmd)
{
	char	*dir;
	char	*full_dir;
	int		i;

	i = 0;
	while (path[i])
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
		i++;
	}
	return (NULL);
}

static char	*get_path(char **envp, char *cmd)
{
	int		i;
	char	**path;
	char	*fullpath;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			// path = ft_split(envp[i] + 5, ':');
			path = ft_split(get_value_env("PATH"), ':'); // Можно вынести за цикл
			if (!path)
				return (NULL);
			fullpath = path_combine(path, cmd);
			ft_free_split(path);
			return (fullpath);
		}
		i++;
	}
	return (NULL);
}

static int	check_red(char *str)
{
	if (!(strncmp(str, ">\0", 2))
		|| !(strncmp(str, "<\0", 2))
		|| !(strncmp(str, ">>\0", 3)))
		return (1);
	else
		return (0);
}

static int	output_red(char *output, int status)
{
	int	fd;

	fd = 0;
	if (status == 0)
		fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (status == 1)
		fd = open(output, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
		perror(output);
	return (fd);
}

static int	input_red(char *input)
{
	int	fd;

	fd = 0;
	fd = open(input, O_RDONLY);
	if (fd < 0)
		perror(input);
	return (fd);
}

static int	get_file_descriptor(char *red, char *file, t_pipex *p)
{
	if (!(strncmp(red, ">\0", 2)))
	{
		p->std_out = output_red(file, CREATE);
		return (p->std_out);
	}
	else if (!(strncmp(red, ">>\0", 3)))
	{
		p->std_out = output_red(file, APPEND);
		return (p->std_out);
	}
	else if (!(strncmp(red, "<\0", 2)))
	{
		p->std_in = input_red(file);
		return (p->std_in);
	}
	return (0);
}

static int	redirection_case(char **argv, int *i, t_pipex *p)
{
	int fd;

	fd = get_file_descriptor(argv[*i], argv[*i + 1], p);
	if (fd == -1)
		return (1);
	if (argv[*i + 2] == 0)
		return (1);
	else
		(*i)++;
	return (0);
}

static char	**get_cmd(char **argv, t_pipex *p)
{
	int 	i;
	char	**cmd;
	char	*str;
	char	*space;
	char	*tmp1;
	char	*tmp2;

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
		{
			tmp1 = ft_empty(str);
			tmp2 = ft_strjoin(tmp1, argv[i]);
			space = ft_strdup(" ");
			str = ft_strjoin(tmp2, space);
		}
		i++;
		free(space);
		free(tmp1);
		free(tmp2);
	}
	cmd = ft_split(str, ' ');
	free(str);
	return (cmd);
}

static int	child_process(char **argv, t_pipex *p, char **envp)
{
	char	*path;
	char	**cmd;

	cmd = get_cmd(argv, p);
	dupper(p->std_in, p->std_out);
	if (!cmd || !ft_isbuiltin(cmd))
		return (FAILURE);
	path = get_path(envp, cmd[0]);
	if (!path)
	{
		ft_err_print(cmd[0], NULL, "command not found");
		ft_free_split(cmd);
		return (EXEC_NOTFOUND);
	}
	else
		execve(path, cmd, envp);
	ft_free_split(cmd);
	free(path);
	return (SUCCESS);
}

static int	wait_exit(t_pipex	*p)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i <= p->pipe_num)
	{
		waitpid(p->pipes[i], &status, 0);
		i++;
	}
	free(p->pipes);
	return (status);
}

static int	go_next_cmd(int j, char **argv)
{
	while (argv[j])
	{
		if (argv[j][0] == '|' && argv[j][1] == '\0')
			return (++j);
		j++;
	}
	return (-1);
}

static int	pipe_execute(char **argv, t_pipex *p, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i <= p->pipe_num)
	{
		if (j < 0)
			break ;
		if (i == p->pipe_num)
			p->std_out = 1;
		else if (p->pipe_num > 0)
		{
			pipe(p->pipefd);
			p->std_out = p->pipefd[1];
		}
		p->pipes[i] = fork();
		if (p->pipes[i] == -1)
			exit(1);
		if (p->pipes[i] == 0)
			child_process(&argv[j], p, envp);
		close_pipe(p);
		j = go_next_cmd(j, argv);
		i++;
	}
	dupper(p->in, p->out);
	return(wait_exit(p));
}

// static void wait_child(pid_t pid)
// {
// 	int	status;

// 	status = 0;
// 	waitpid(pid, &status, 0);
// 	// return (status);
// }

static int ft_child(pid_t *pid, char **cmd, char *path, char **envp)
{
	int status;

	*pid = fork();
	status = 0;
	if (*pid == -1)
	{
		ft_free_split(cmd);
		return (print_err_errno(NULL, NULL));
	}
	if (*pid == 0)
	{
		path = get_path(envp, cmd[0]);
		if (!path)
		{
			ft_err_print(cmd[0], NULL, "command not found");
			return (EXEC_NOTFOUND);
		}
		else
			execve(path, cmd, envp);
		if (errno == ENOENT)
			status = EXEC_NOTFOUND;
		else
			status = EXEC_NOEXEC;
		print_err_errno(cmd[0], NULL);
	}
	return (status);
}

static int	no_pipe_case(char **argv, t_pipex *p, char **envp)
{
	char	*path;
	char	**cmd;
	pid_t	pid;
	int		status;

	p->std_out = 1;
	path = NULL;
	cmd = get_cmd(argv, p);
	dupper(p->std_in, p->std_out);
	if (!cmd)
		return (FAILURE);
	if (handle_expand(cmd) == FAILURE)
		return (-1);
	status = ft_isbuiltin(cmd);
	if (status != FAILURE)
	{
		set_exit_status(status);
		dupper(p->in, p->out);
		return (status);
	}
	status = ft_child(&pid, cmd, path, envp);
	set_exit_status(status);
	// wait_child(pid);
	waitpid(pid, &status, 0);
	// set_exit_status(WEXITSTATUS(status));
	dupper(p->in, p->out); // возвращаем std_in и std_out на свои места, иначе при перенаправлении ввод останется в файле
	ft_free_split(cmd);
	free(path);
	return (status);
}

static int	ft_piper(char **argv, t_pipex *p, char **envp)
{
	p->pipe_num = pipe_counter(argv);
	if (p->pipe_num == 0)
	{
		if (no_pipe_case(argv, p, envp) != SUCCESS)
			return (1);
	}
	p->pipes = (int *)malloc(sizeof(int) * (p->pipe_num + 1));
	if (!(p->pipes))
	{
		ft_err_print(NULL, NULL, strerror(ENOMEM));
		return (1);
	}
	return (0);
}

int	ft_execute(char **argv, char **envp)
{
	t_pipex	p;

	p.in = dup(0);
	p.out = dup(1);
	p.std_in = 0;
	p.std_out = 1;
	p.pipefd[1] = 1;
	p.close = 1;
	if (here_doc_check(argv))
		return (0); // предусмотреть случай для heredoc
	if (!ft_piper(argv, &p, envp))
		set_exit_status(pipe_execute(argv, &p, envp));
	return (get_exit_status());
}