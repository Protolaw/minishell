#include "exec.h"

int	pipe_counter(char **argv)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while(argv[++i])
		if (ft_strncmp(argv[i], "|\0", 2) == 0)
			count++;
	return (count);	
}

void close_pipe(t_pipex *p)
{
	close(p->pipefd[1]);
	if (p->close)
		close(p->close);
	p->std_in = p->pipefd[0];
	p->close = p->std_in;
}

void	dupper(int fd1, int fd2)
{
	if (dup2(fd1, 0) == -1)
		exit(1);
	if (dup2(fd2, 1) == -1)
		exit(1);
}

int	go_next_cmd(int j, char **argv)
{
	while (argv[j])
	{
		if (argv[j][0] == '|' && argv[j][1] == '\0')
			return (++j);
		j++;
	}
	return (-1);
}

int	wait_exit(t_pipex	*p)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i <= p->pipe_num)
	{
		waitpid(p->pipes[i], &status, 0);
		set_exit_status(WEXITSTATUS(status));
		i++;
	}
	free(p->pipes);
	return (status);
}