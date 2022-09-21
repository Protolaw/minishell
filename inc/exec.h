
#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

# define EXEC_NOEXEC	126
# define EXEC_NOTFOUND	127

int     get_exit_status(void);
void	set_exit_status(int status);
int     *exit_status_pointer(void);
void	free_exit(int status);

int     check_red(char *str);
int     redirection_case(char **argv, int *i, t_pipex *p);

char	**get_cmd(char **argv, t_pipex *p);
int     do_cmd(char **cmd, int status);

int     pipe_counter(char **argv);
void    close_pipe(t_pipex *p);
void	dupper(int fd1, int fd2);
int     wait_exit(t_pipex	*p);
int     go_next_cmd(int j, char **argv);

int     no_pipe_case(char **argv, t_pipex *p);

#endif