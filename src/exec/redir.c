#include "exec.h"

int	check_red(char *str)
{
	if (!(strncmp(str, ">\0", 2))
		|| !(strncmp(str, "<\0", 2))
		|| !(strncmp(str, ">>\0", 3)))
		return (1);
	else
		return (0);
}

int	output_red(char *output, int status)
{
	int	fd;

	fd = 0;
	if (status == 0)
		fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (status == 1)
		fd = open(output, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
		perror(output);
	return (fd);
}

int	input_red(char *input)
{
	int	fd;

	fd = 0;
	fd = open(input, O_RDONLY);
	if (fd < 0)
		perror(input);
	return (fd);
}

int	get_file_descriptor(char *red, char *file, t_pipex *p)
{
	if (!(strncmp(red, ">\0", 2)))
	{
		p->std_out = output_red(file, CREATE);
		return (p->std_out);
	}
	else if (!(strncmp(red, ">>\0", 3)))
	{
		p->std_out = output_red(file, APPEND);
		return (p->std_out);
	}
	else if (!(strncmp(red, "<\0", 2)))
	{
		p->std_in = input_red(file);
		return (p->std_in);
	}
	return (0);
}

int	redirection_case(char **argv, int *i, t_pipex *p)
{
	int fd;

	fd = get_file_descriptor(argv[*i], argv[*i + 1], p);
	if (fd == -1)
		return (1);
	if (argv[*i + 2] == 0)
		return (1);
	else
		(*i)++;
	return (0);
}
