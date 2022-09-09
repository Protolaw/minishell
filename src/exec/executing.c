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

static char	*get_path(char *cmd)
{
	char	**path;
	char	*fullpath;

	path = ft_split(get_value_env("PATH"), ':'); // Можно вынести за цикл
	if (!path)
		return (NULL);
	fullpath = path_combine(path, cmd);
	ft_free_split(path);
	return (fullpath);
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


static char	**get_cmd(char **argv, t_pipex *p)
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

static int	child_process(char **argv, t_pipex *p)
{
	char	**cmd;
	int status;

	cmd = get_cmd(argv, p);
	dupper(p->std_in, p->std_out);
	status = 0;
	if (!cmd || handle_expand(cmd) == FAILURE)
		return (-1);
	status = ft_isbuiltin(cmd);
	if (status == SUCCESS)
	{
		set_exit_status(status);
		dupper(p->in, p->out);
		return (0);
	}
	else if (status == FAILURE)
	{
		status = do_cmd(cmd, status);
		set_exit_status(status);
		dupper(p->in, p->out);
		ft_free_split(cmd);
		return (0);
	}
	return (-1);
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

static int	pipe_execute(char **argv, t_pipex *p)
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
			child_process(&argv[j], p);
		close_pipe(p);
		j = go_next_cmd(j, argv);
		i++;
	}
	dupper(p->in, p->out);
	return(wait_exit(p));
}

static int ft_child_monopipe(pid_t *pid, char **cmd)
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
		status = do_cmd(cmd, status);
		set_exit_status(status);
	}
	return (status);
}

static int	no_pipe_case(char **argv, t_pipex *p)
{
	char	**cmd;
	pid_t	pid;
	int		status;

	p->std_out = 1;
	cmd = get_cmd(argv, p);
	dupper(p->std_in, p->std_out);
	if (!cmd || handle_expand(cmd) == FAILURE)
		return (-1);
	status = ft_isbuiltin(cmd);
	if (status == SUCCESS)
	{
		set_exit_status(status);
		dupper(p->in, p->out);
		return (0);
	}
	else if (status == FAILURE)
	{
		status = ft_child_monopipe(&pid, cmd);
		if (!status)
		{
			waitpid(pid, &status, 0);
			set_exit_status(WEXITSTATUS(status));
		}
		dupper(p->in, p->out); // возвращаем std_in и std_out на свои места, иначе при перенаправлении ввод останется в файле
	}
	ft_free_split(cmd);
	return (0);
}

static int	ft_piper(char **argv, t_pipex *p)
{
	p->pipe_num = pipe_counter(argv);
	if (p->pipe_num == 0)
	{
		if (no_pipe_case(argv, p) != -1)
			return (0);
	}
	p->pipes = (int *)malloc(sizeof(int) * (p->pipe_num + 1));
	if (!(p->pipes))
		return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
	return (1);
}

int	ft_execute(char **argv)
{
	t_pipex	p;
	int proc;

	p.in = dup(0);
	p.out = dup(1);
	p.std_in = 0;
	p.std_out = 1;
	p.pipefd[1] = 1;
	p.close = 0;
	if (here_doc_check(argv))
		return (0); // предусмотреть случай для heredoc
	proc = ft_piper(argv, &p);
	if (!proc)
		return (get_exit_status());
	if (proc == 1)
		pipe_execute(argv, &p);
	return (get_exit_status());
}