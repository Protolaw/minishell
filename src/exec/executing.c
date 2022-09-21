#include "exec.h"

void	child_process(char **argv, t_pipex *p)
{
	char	**cmd;
	int		status;

	cmd = get_cmd(argv, p);
	if (!cmd || handle_expand(cmd) == FAILURE)
		exit(1);
	dupper(p->std_in, p->std_out);
	status = ft_isbuiltin(cmd);
	if (status == SUCCESS)
	{
		set_exit_status(status);
		exit(get_exit_status());
	}
	if (status == FAILURE)
	{
		status = do_cmd(cmd, status);
		set_exit_status(status);
		if (status)
		{
			ft_free_split(cmd);
			exit(get_exit_status());
		}
	}
}

int fork_pipe(t_pipex *p, char **argv, int i, int j)
{
	p->pipes[i] = fork();
	if (p->pipes[i] == -1)
		exit(1);
	if (p->pipes[i] == 0)
		child_process(&argv[j], p);
	close_pipe(p);
	j = go_next_cmd(j, argv);
	return (j);
}

static void	pipe_execute(char **argv, t_pipex *p)
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
		j = fork_pipe(p, argv, i, j);
		i++;
	}
	wait_exit(p);
	dupper(p->in, p->out);
}

static int	ft_piper(char **argv, t_pipex *p)
{
	p->pipe_num = pipe_counter(argv);
	if (p->pipe_num == 0)
		if (no_pipe_case(argv, p) != -1)
			return (0);
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
	// if (here_doc_check(argv, &p, g_env))
	// 	return (0); // предусмотреть случай для heredoc
	// here_doc_check(argv, &p, g_env);
	proc = ft_piper(argv, &p);
	// if (!proc)
	if (p.pipe_num == 0)
		return (get_exit_status());
	if (proc == 1)
		pipe_execute(argv, &p);
	return (get_exit_status());
}