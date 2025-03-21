/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:47:18 by kcisse            #+#    #+#             */
/*   Updated: 2025/03/21 12:02:24 by kcisse           ###   ########.fr       */
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
#include "libft.h"

# define MAX_MAP_SIZE 100
# define WIDTH 1280
# define HEIGHT 720

# define T 119 // w
# define B 115 // s
# define L 97  // a
# define R 100 // d
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

typedef struct s_game_info
{
	double		x;
	double		y;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	int			floor_color[3];
	int			ceiling_color[3];
	char		**map;
}				t_game_info;

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
	t_game_info	game_info;
}				t_game;

// PARSING
//		FILE
t_game_info		*parse_file(char *file);
void			init_game_info(t_game_info *info);
void			ft_trim(char *line);
int				file_exist(char *str, char **texture_var);
int				ft_tab_len(char **tab);
int				check_file_name(char *file_name);
//		MAP
char			**parse_map(int fd, char *line);
int				check_map_wall(char **map, int map_height);
int				check_map_content(char **map);
//		TEXTURE
int				check_texture(t_game_info *info);
int				parse_texture(char *str, t_game_info *info);
int				parse_color(char *str, int *texture_var);
int				check_is_valid_color(char **colors, int *texture_var);

#endif
