
#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

# define EXEC_NOEXEC	126
# define EXEC_NOTFOUND	127

int     get_exit_status(void);
void	set_exit_status(int status);
int     *exit_status_pointer(void);
void	free_exit(int status);

#endif