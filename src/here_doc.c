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

void    write_in_pipe(char *str, int *p, char **envp)
{
    str = ft_minijoin(str, ft_strdup("\n"));
    ft_putstr_fd(str p[1]);
    free(str);
    str = 0;
}

int here_doc(char *stop, char **envp)
{
    char *str;
    int p[2];

    pipe(p);
    str = NULL;
    while (1)
    {
        str = readline("heredoc> ");
        if (str == 0)
        {
            printf("\n");
            break ;
        }
        if (ft_strncmp(stop, str) == 0)
            break ;
        write_in_pipe(str, p, envp); // envp для $
    }
    free(str);
    close(p[1]);
    return (p[0]);
}

int ft_here(int *fd, char *stop, char **envp)
{
    int tmp_fd;

    tmp_fd = 0;
    if (fd == -1)
    {
        tmp_fd = here_doc(stop, envp);
        close(tmp_fd);
    }
    else
    {
        if (*fd != 0)
            close(*fd);
        *fd = here_doc(stop, envp);
    }
    return (1);
}

void    check_here_red(int *fd, t_list *fds, char **argv, char **envp)
{
    int i;

    i = 0;
    while(argv[i] && *fd != -1)
    {
        if (ft_strncmp(argv[i], "<<\0", 3) == 0)
        {
            if (ft_here(fd, argv[i + 1], envp) == 0)
                return ;
        }
        else if (ft_strncmp(argv[i], "<\0", 2) == 0)
        {
            if (*fd != 0)
		        close(*fd);
	        *fd = open(argv[i + 1], O_RDONLY);
            if (*fd == -1)
                return; //Ошибку надо записывать, после полного прохода - вывод в консоль
        }
        else if (ft_strncmp(argv[i], "|\0", 2) == 0)
        {
            ft_lstadd_back(fds, ft_lstnew(*fd))
            *fd = 0;
        }
        i++;
    }
}

void    delete_here(char **argv)
{

}

t_list get_fds(char **argv, char **envp)
{
    t_list *fds;
    int fd;
    
    fds = 0;
    fd = 0;
    check_here_red(&fd, &fds, argv, envp);
    ft_lstadd_back(&fds, ft_lstnew(fd));
    delete_here(argv); // удалить << и < из argv
    //вывод накопившихся ошибок
    return(fds);
}

int here_doc_check(char **argv, t_pipex	*p, char **envp)
{
    p->fds_here_doc = 0;
    if (here_doc_check(argv))
    {
       p->fds_here_doc = get_fds(argv, envp);
       if (argv == 0 || p->fds_here_doc == 0)
       {
           return (1);
       }
       p->std_in = *(int *)p->fds_here_doc->content;
       p->fds_here_doc = p->fds_here_doc->next;
    }
    return (0);
}