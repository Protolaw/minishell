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

# define CLOSE "\001\033[0m\002"
# define BLOD "\001\033[1m\002"
# define BEGIN(x,y) "\001\033["#x";"#y"m\002"

# define SUCCESS 0
# define FAILURE 1

# define INPUT 0
# define OUTPUT 1

# define CREATE 0
# define APPEND 1

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

int		ft_newline_error(void);
int		ft_quotes_error(int d_q, int s_q);
int		ft_syntax_error(int d, char c);

int 	ft_strlen1(char *s);
int		special_character_check(char *str);
char	**ft_parse(char *str);
char	**minishell_split(char *str);
char	**remove_quotes(char **argv);
char	*ft_empty(char *s1);
char	*ft_minijoin(char *s1, char *s2);
int		words_counter(char *str);
void	ft_scroller(char *str, char q, int *i, int *count);
int		quotes_check(char *str);
void	free_mass(char **mass);
void	ft_execute(char **argv, char **envp);
char	*ft_minisubstr(char *s, int start, int len);

int		brackets_check(char *str);

#endif
