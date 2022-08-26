#include "exec.h"

int	*exit_status_pointer(void)
{
	static int	last_exit_status = 0;

	return (&last_exit_status);
}

int	get_exit_status(void)
{
	return (*exit_status_pointer());
}

void	set_exit_status(int status)
{
	if (status == -1)
		status = EXIT_FAILURE;
	*exit_status_pointer() = status;
}