/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:47:18 by kcisse            #+#    #+#             */
/*   Updated: 2025/03/14 12:10:41 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>

# define WIDTH 1280
# define HEIGHT 720

# define T 119 //w
# define B 115 //s
# define L 97 //a
# define R 100 //d
# define LEFT 65361
# define RIGHT 65363
// # define T 65362 //w
// # define B 65364 //s
// # define L 65361 //a
// # define R 65363 //d
# define PI 3.14159265359
# define N (3 * PI / 2)
# define S PI / 2
# define E 0
# define W PI

typedef struct s_player
{
	double		x;
	double		y;
	double		pdx;
	double		pdy;
	double		pa;
	double		angle;

	bool		key_up;
	bool		key_down;
	bool		key_left;
	bool		key_right;

	bool		left_rotate;
	bool		right_rotate;
}				t_player;
typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;
typedef struct s_texture
{
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	t_color		*floor_color;
	t_color		*ceiling_color;
}				t_texture;

typedef struct s_map
{
	void		*mlx;
	void		*win;
	double posX, posY;     // Position du joueur
	double dirX, dirY;     // Direction du regard
	double planeX, planeY; // Plan de la caméra
}				t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_player	player;
}				t_game;

int				check_map_file(char *map, t_texture *textures);

#endif
