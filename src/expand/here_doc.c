// #include "minishell.h"
#include "expand.h"

int	here_doc_check(char **argv)
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

// void    write_in_pipe(char *str, int *p, char **envp)
// {

// }

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
        if (ft_strncmp(stop, str, ft_strlen(str)) == 0)
            break ;
        //write_in_pipe(str, p, envp); // envp для $
    }
	envp = envp;
    free(str);
    close(p[1]);
    return (p[0]);
}

int ft_here(int *fd, char *stop, char **envp)
{
    int tmp_fd;

    tmp_fd = 0;
    if (*fd != -1)
    {
        *fd = here_doc(stop, envp);
        return (0);
    }
    if (*fd == -1)
    {
        tmp_fd = here_doc(stop, envp);
        close(tmp_fd);
        return (0);
    }
    return (1);
}

void    check_here_red(int *fd, t_list fds, char **argv, char **envp)
{
    int i;

    i = 0;
    while(argv[i] && *fd == -1)
    {
        if(ft_strncmp(argv[i], "<<\0", 3) == 0)
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
            //ft_lstadd_back(fds, ft_lstnew(Опознаватель пайпа))
            *fd = 0;
        }
        i++;
    }
}

t_list get_fds(char **argv, char **envp)
{
    t_list *fds;
    int fd;
    
    fds = 0;
    fd = 0;
    check_here_red(&fd, &fds, argv, envp);
    if (fd == -1)
        return (NULL);
    return (fds);
}

void    here_doc_check_argv(char **argv, t_pipex	*p, char **envp)
{
    if (here_doc_check(argv))
    {
       p->fds_here_doc = 0; //Вводим список в котором будут сохраняться fd до heredoc включительно(сделал пока листом, в дальнейшем мб поменяем на двумерник)
       p->fds_here_doc = get_fds(argv, envp);
    }
    return ;
}
