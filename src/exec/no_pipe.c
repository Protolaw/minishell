#include "exec.h"

static int ft_child_no_pipe(pid_t *pid, char **cmd)
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

void bin_cmd_handle(char **cmd, t_pipex *p)
{
    int status;
    pid_t	pid;

    status = ft_child_no_pipe(&pid, cmd);
    if (!status)
    {
        waitpid(pid, &status, 0);
        set_exit_status(WEXITSTATUS(status));
        dupper(p->in, p->out);
    }
    else
    {
        ft_free_split(cmd);
        exit(get_exit_status());
    }
}

int	no_pipe_case(char **argv, t_pipex *p)
{
	char	**cmd;
	int		status;

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
        bin_cmd_handle(cmd, p);
	ft_free_split(cmd);
	return (0);
}