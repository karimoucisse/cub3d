#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}			t_color;
typedef struct s_texture
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	t_color	*floor_color;
	t_color	*ceiling_color;
}			t_texture;

int			check_map_file(char *map, t_texture *textures);

#endif
