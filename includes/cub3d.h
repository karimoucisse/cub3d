/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:47:18 by kcisse            #+#    #+#             */
/*   Updated: 2025/03/26 15:03:14 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>

# define PI 3.14159265359
# define MAX_MAP_SIZE 100
# define WIDTH 980
# define HEIGHT 620
# define TILE 34
# define FOV 60 * (PI / 180)
# define T 119 // w
# define B 115 // s
# define L 97  // a
# define R 100 // d
# define LEFT 65361
# define RIGHT 65363
# define N (3 * PI / 2)
# define S PI / 2
# define E 0
# define W PI

typedef struct s_raycast
{
	bool		was_hit_vertical;
	double		v_hit_posx;
	double		v_hit_posy;
	double		v_hit_dist;
	double		h_hit_posx;
	double		h_hit_posy;
	double		h_hit_dist;
	double		wall_hitx;
	double		wall_hity;
	double		wall_hit_dist;
	double		wall_height;
	int			color;
}				t_raycast;

typedef struct s_player
{
	double		x;
	double		y;
	// double		dirX;
	// double		dirY;
	// double		planeX;
	// double		planeY;
	bool		key_up;
	bool		key_down;
	bool		key_left;
	bool		key_right;

	bool		left_rotate;
	bool		right_rotate;

	double		radius;
	int turn_dir; // -1 == left, +1 == right
	int walk_dir; // -1 == back, +1 == front
	double		rot_angle;
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
	void		*mlx_ptr;
	void		*mlx_win;
	void		*img_ptr;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_player	player;
	t_game_info	*game_info;
	t_raycast	raycast_info;
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
