#include "cub3d.h"

void print_error(char *err_msg)
{
	write(1, "Error\n", 6);
	if(err_msg)
		write(1, err_msg, ft_strlen(err_msg));
	exit(1);
}
