
#include "expand.h"

static char	*get_heredoc(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], "<<", 3) == 0)
			return (argv[i + 1]);
		i++;
	}
	return (NULL);
}

static int	exit_close_fds(int fd1, int fd2, int exit_status)
{
	if (fd1 != -1)
		close(fd1);
	if (fd1 != -1)
		close(fd2);
	return (exit_status);
}

static void	wait_for_heredoc(t_pipex	*p)
{
	if (p->out != 1)
	{
		close(p->out);
		p->out = 1;
	}
}

int	here_doc_check(char **argv, t_pipex	*p)
{
	int		end[2];
    char    *heredoc;
    char    *buf;
    char    *str;

	if (pipe(end) == -1)
		return (ft_err_print(NULL, NULL, "pipe error"));
	p->in = end[0];
	heredoc = get_heredoc(argv);
	if (heredoc == NULL)
		return (exit_close_fds(end[0], end[1], 1));
	while (1)
	{
		str = readline("> ");
		if (str == NULL)
			return (exit_close_fds(end[1], -1, 0));
		if (ft_strncmp(str, heredoc, 3) == 0)
			break ;
        buf = ft_minijoin(str, ft_strdup("\n"));
        expand_elem(buf, NULL);
        ft_putstr_fd(buf, end[1]);
		free(buf);
	}
    free(str);
	close(end[1]);
	wait_for_heredoc(p);
	return (1);
}