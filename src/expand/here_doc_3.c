#include "minishell.h"

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

char *str_expand(char *elem)
{
    int i;
    char *dest;

    if (!elem || !ft_strchr(elem, '$'))
        return (elem);
    dest = ft_strdup("");
	if (dest == NULL)
		return (NULL);
    i = 0;
    while (elem[i])
    {
        if (get_exp(elem, &dest, &i) != SUCCESS)
		{
			free(dest);
			return (NULL);
		}
		i++;
    }
    return (dest);
}

static void    write_in_pipe(char *str, int *p)
{
    str = ft_minijoin(str, ft_strdup("\n"));
    str = str_expand(str);
    ft_putstr_fd(str, p[1]);
    // Проблема в дескрипторах
    free(str);
    str = 0;
}

static int here_doc(char *stop)
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
            break ;
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

static int ft_here(int *fd, char *stop)
{
    int tmp_fd;

    tmp_fd = 0;
    if (*fd == -1)
    {
        tmp_fd = here_doc(stop);
        close(tmp_fd);
    }
    else
    {
        if (*fd != 0)
        {
            close(*fd);
        }
        *fd = here_doc(stop);
    }
    return (1);
}

static void    check_here_red(int *fd, t_list **fds, char **argv)
{
    int i;
    t_list *new_node;

    i = 0;
    while(argv[i] && *fd != -1)
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
                return; //Ошибку надо записывать, после полного прохода - вывод в консоль
        }
        else if (ft_strncmp(argv[i], "|\0", 2) == 0)
        {
            new_node = ft_lstnew(fd);
            ft_lstadd_back(fds, new_node);
            *fd = 0;
        }
        i++;
    }
}

int check_redirect_here(char **argv)
{
    int i;

    i = 0;
    while (argv[i])
    {
        if (ft_strncmp(argv[i], "<<\0", 3) == 0
            || ft_strncmp(argv[i], "<\0", 2) == 0)
            return (1);
        i++;
    }
    return (0);
}

void	del(void *ptr)
{
	free(ptr);
}

void delete_extra(t_list *first, t_list **second)
{
	t_list	*prev;
	t_list	*node;

	node = 0;
	first = *second;
	while (first != NULL && (ft_strncmp(first->content, "<<\0", 4) != 0
			&& ft_strncmp(first->content, "<\0", 3) != 0))
	{
		prev = first;
		first = first->next;
	}
	if (first->next != NULL)
	{
		node = first;
		prev->next = first->next->next;
		node->next->next = 0;
		ft_lstclear(&node, del);
	}
	else
		prev = NULL;
}

void delete_here(t_list **to_delete)
{
    t_list *tmp;

    tmp = *to_delete;


    if ((tmp != NULL) && ((ft_strncmp(tmp->content, "<<\0", 3) == 0)
        || ft_strncmp(tmp->content, "<\0", 2) == 0))
    {
        *to_delete = tmp->next->next;
    }
    else
        delete_extra(tmp, to_delete);
    if (*to_delete != NULL && check_redirect_here((char**)to_delete))
        delete_here(to_delete);
}

static void write_in_list(t_list *to_delete, char **argv)
{
    int i;
    t_list	*new_node;

    i = 0;
    while (argv[i])
    {
        new_node = ft_lstnew(ft_strdup(argv[i]));
        ft_lstadd_back(&to_delete, new_node);
        i++;
    }
}

static t_list *get_fds(char **argv)
{
    t_list *fds;
    t_list *to_delete;
    int fd;
    
    fds = 0;
    fd = 0;
    to_delete = ft_lstnew(0);
    check_here_red(&fd, &fds, argv);
    ft_lstadd_back(&fds, ft_lstnew(ft_strdup((char *)&fd)));
    write_in_list(to_delete, argv);
    // delete_here(to_delete); // удалить << и < из argv

    ft_lstclear(&to_delete, free);
    
    //вывод накопившихся ошибок
    return (fds);
}

int here_doc_check(char **argv, t_pipex	*p)
{
    p->fds_here_doc = 0;
    if (heredoc_check(argv))
    {
        p->fds_here_doc = get_fds(argv);
        if (argv == 0 || p->fds_here_doc == 0)
        {
            return (1);
        }
        p->std_in = *(int *)p->fds_here_doc->content;
        // p->fds_here_doc = p->fds_here_doc->next;
        ft_lstdelone(p->fds_here_doc, free);
        return(1);
    }
    return (0);
}