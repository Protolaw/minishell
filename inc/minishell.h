#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>

# include "../libft/libft.h"
# include "env.h"
# include "lexer.h"
# include "expand.h"
# include "builtin.h"
# include "utils.h"

# define CLOSE "\001\033[0m\002"
# define BLOD "\001\033[1m\002"
# define BEGIN(x,y) "\001\033["#x";"#y"m\002"

# define SHELL_NAME "Minishell"

# define SUCCESS 0
# define FAILURE 1

# define INPUT 0
# define OUTPUT 1

# define CREATE 0
# define APPEND 1

# define EXIT_CTRL_D 130

extern char	**g_env;

typedef struct s_minisplit
{
	int	i;
	int	row;
	int	start;
}	t_minisplit;

typedef struct s_pipex
{
	int		in;
	int		out;
	int		std_in;
	int		std_out;
	int		close;
	int		*pipes;
	int		pipefd[2];
	int		pipe_num;
	t_list	*fds_here_doc;
}	t_pipex;

# include "exec.h"

int		ft_newline_error(void);
int		ft_quotes_error(int d_q, int s_q);
int		ft_syntax_error(int d, char c);

int		special_character_check(char *str);
char	**ft_parse(char *str);
char	**remove_quotes(char **argv);
int		quotes_check(char *str);
void	free_mass(char **mass);
char	*ft_minijoin(char *s1, char *s2);
int		words_counter(char *str);
void	ft_scroller(char *str, char q, int *i, int *count);

int		ft_execute(char **argv);
char	*ft_minisubstr(char *s, int start, int len);

// Parse cases
int		case_double_quotes(t_minisplit *m, char *str, char **tmp);
int		case_single_quotes(t_minisplit *m, char *str, char **tmp);
int		case_no_quotes(t_minisplit *m, char *str, char **tmp);
int		case_redirection(t_minisplit *m, char *str, char **tmp);

#endif
