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
			path = ft_split(envp[i] + 5, ':');
			if (!path)
				return (NULL);
			fullpath = path_combine(path, cmd);
			free_mass(path);
			return (fullpath);
		}
		i++;
	}
	perror("Path not found");
	exit(1);
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
			if (!str)
			{
				str = (char *)malloc(sizeof(char) * 1);
				str[0] = '\0';
			}
			str = ft_strjoin(str, argv[i]);
			str = ft_strjoin(str, ft_strdup(" "));
		}
		i++;
	}
	cmd = ft_split(str, ' ');
	free(str);
	return (cmd);
}

static int check_built_in(char **cmd, char **envp)
{
	if (cmd || envp)
		return 0;
	return 0; // Случай как поступить с built_in тут разберешь? 
}

static void	child_process(char **argv, t_pipex *p, char **envp)
{
	char	*path;
	char	**cmd;

	cmd = get_cmd(argv, p);
	dupper(p->std_in, p->std_out);
	if (!cmd || check_built_in(cmd, envp)) // провервка команды на built-in
		exit(1);
	path = get_path(envp, cmd[0]);
	execve(path, cmd, envp);
	perror("cmd execution error");
	free_mass(cmd);
	free(path);
	exit(1);
}

static void	wait_exit(t_pipex	*p)
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

static void	pipe_execute(char **argv, t_pipex *p, char **envp)
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
	wait_exit(p);
	dupper(p->in, p->out);
}

static void wait_child(pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
}

static void ft_child(pid_t *pid, char **cmd, char *path, char **envp)
{
	*pid = fork();
	if (*pid == -1)
		exit(1);
	if (*pid == 0)
	{
		path = get_path(envp, cmd[0]);
		execve(path, cmd, envp);
		perror("cmd execution error");
		free_mass(cmd);
		free(path);
		exit(1);
	}
}

static void	no_pipe_case(char **argv, t_pipex *p, char **envp)
{
	char	*path;
	char	**cmd;
	pid_t	pid;

	p->std_out = 1;
	path = NULL;
	cmd = get_cmd(argv, p);
	dupper(p->std_in, p->std_out);
	if (!cmd || check_built_in(cmd, envp))
		exit(1);
	ft_child(&pid, cmd, path, envp);
	wait_child(pid);
	dupper(p->in, p->out); // возвращаем std_in и std_out на свои места, иначе при перенаправлении ввод останется в файле
}

static int	ft_piper(char **argv, t_pipex *p, char **envp)
{
	p->pipe_num = pipe_counter(argv);
	if (p->pipe_num == 0)
	{
		no_pipe_case(argv, p, envp);
		return (0);
	}
	p->pipes = (int *)malloc(sizeof(int) * (p->pipe_num + 1));
	if (!(p->pipes))
		exit(1);
	return (1);
}

void	ft_execute(char **argv, char **envp)
{
	t_pipex	p;

	p.in = dup(0);
	p.out = dup(1);
	p.std_in = 0;
	p.std_out = 1;
	p.pipefd[1] = 1;
	if (here_doc_check(argv))
		return ; // предусмотреть случай для heredoc
	if (ft_piper(argv, &p, envp))
		pipe_execute(argv, &p, envp);
}