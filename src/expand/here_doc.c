// // #include "minishell.h"
#include "expand.h"

static int	heredoc_check(char **argv)
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

void    write_in_pipe(char *str, int *p)
{
    str = ft_minijoin(str, ft_strdup("\n"));
    expand_elem(str, NULL);
    ft_putstr_fd(str, p[1]);
    free(str);
    str = NULL;
}

int	exit_close_fds(int fd1, int fd2, int exit_status)
{
	if (fd1 != -1)
		close(fd1);
	if (fd1 != -1)
		close(fd2);
	return (exit_status);
}

int here_doc_readline(char *stop)
{
    char *str;
    int p[2];

    if (pipe(p) == -1)
    {
        ft_err_print(NULL, NULL, "pipe error");
        exit(1);
    }
    str = NULL;
    while (1)
    {
        str = readline("heredoc> ");
        if (str == 0)
        {
            write(1, "\n", 1);
            break;
            // return (exit_close_fds(p[1], -1, EXIT_SUCCESS));
        }
        if ((ft_strncmp(stop, str, ft_strlen(stop)) == 0) 
            && (int)ft_strlen(stop) == (int)ft_strlen(str))
                break;
        write_in_pipe(str, p);
    }
    free(str);
    close(p[1]);
    return (p[0]);
}

int ft_here(int *fd, char *stop)
{
    int tmp_fd;

    tmp_fd = 0;
    if (*fd == -1)
    {
        tmp_fd = here_doc_readline(stop);
        close(tmp_fd);
        return (0);
    }
    else
    {
        if (*fd != 0)
            close(*fd);
        *fd = here_doc_readline(stop);
        return (0);
    }
    return (1);
}

void    check_here_red(int *fd, t_list *fds, char **argv)
{
    int i;
    t_list	*new_node;

    i = 0;
    while (argv[i] && *fd != -1)
    {
        if (ft_strncmp(argv[i], "<<\0", 3) == 0)
        {
            if (ft_here(fd, argv[i + 1]) == 0)
                return ;
        }
        else if (ft_strncmp(argv[i], "<\0", 2) == 0)
        {
            if (*fd != 0)
		        close(*fd);
	        *fd = open(argv[i + 1], O_RDONLY);
            if (*fd == -1)
            {
                return; //Ошибку надо записывать, после полного прохода - вывод в консоль
            }
        }
        else if (ft_strncmp(argv[i], "|\0", 2) == 0)
        {
            new_node = ft_lstnew(fd);
            ft_lstadd_back(&fds, new_node);
            *fd = 0;
        }
        i++;
    }
}

void    delete_here(char **argv)
{
    char *one;
    char *two;
    char *none;

    one = ft_strdup("<");
    two = ft_strdup("<<");
    none = ft_strdup("");
    split_replace_str(&argv, one, none);
    split_replace_str(&argv, two, none);
    free(one);
    free(two);
}

t_list *get_fds(char **argv)
{
    t_list *fds;
    int fd;
    t_list *new_node;
    
    fd = 0;
    // fds = ft_lstnew(0);
    fds = 0;
    // if(!fds)
        // return (NULL);
    check_here_red(&fd, fds, argv);
    // if(!fds)
    // {
    //     return (NULL);
    // }
    new_node = ft_lstnew(&fd);
    ft_lstadd_back(&fds, new_node);
    // ft_lstadd_back(&fds, (t_list *)&fd);
    // delete_here(argv); // удалить << и < из argv
    //вывод накопившихся ошибок
    // int i = 0;
    // while (argv[i])
    // {
    //     printf("\n%s\n",argv[i]);
    //     i++;
    // }
    // ft_lstclear(p->fds_here_doc, free);
    // ft_lstdelone(new_node, free);
    return (fds);
}

int here_doc_check(char **argv, t_pipex	*p)
{
    p->fds_here_doc = 0;
    if (heredoc_check(argv))
    {
        p->fds_here_doc = get_fds(argv);
        
        printf("%d\n", ft_lstsize(p->fds_here_doc));
        // while (*(int *)p->fds_here_doc->content != 0)
        // {
        // printf("%d\n", *(int *)p->fds_here_doc);
        // printf("%d\n", *(int *)p->fds_here_doc->content);
        if (argv == NULL || p->fds_here_doc == 0)
        {
            // printf("%d\n", *(int *)p->fds_here_doc->content);
            return (1);
        }
        p->std_in = *(int *)p->fds_here_doc->content;
        p->fds_here_doc = p->fds_here_doc->next;
        // }
        // p->fds_here_doc
        // ft_lstclear(&p->fds_here_doc, free);
        // ft_lstdelone(p->fds_here_doc, free);
        return(1);
    }
    return (0);
}
