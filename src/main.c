#include "cub3d.h"

int	main(int ac, char **av)
{
	if (ac != 2)
		return (EXIT_FAILURE);
	if(!check_file_name(av[1]))
		printf("Error\n");
	parse_file(av[1]);
}
