
#include "../inc/builtin.h"

int exec_pwd(void)
{
    char *currdir;

    currdir = NULL;
    currdir = getcwd(currdir, 0);
    if (currdir == NULL)
		  return (ft_err_print(NULL, NULL, strerror(ENOMEM)));
    else
    {
        ft_putendl_fd(currdir, 1);
        ft_free_str(&currdir);
        return (0);
    }
}