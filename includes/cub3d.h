/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knavarre <knavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:47:18 by kcisse            #+#    #+#             */
/*   Updated: 2025/04/12 17:52:06 by knavarre         ###   ########.fr       */
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


# define SUCCESS 0
# define ERROR 1
# define PI 3.14159265359
# define MAX_MAP_SIZE 100
# define WIDTH 980
# define HEIGHT 620
# define TILE 64
# define MINIMAP_TILE 8
# define FOV 60 * (PI / 180)
# define MOVE_SPEED 0.5
# define ROTATION_SPEED 0.010
# define T 119 // w
# define B 115 // s
# define L 97  // a
# define R 100 // d
# define LEFT 65361
# define RIGHT 65363
# define ECHAP 65307
# define N (3 * PI / 2)
# define S PI / 2
# define E 0
# define W PI

typedef struct s_texture
{
	void		*img_ptr;
	char		*addr;
	int			width;
	int			height;
	int			bpp;
	int			line_len;
	int			endian;
	int			*pixels;
}				t_texture;
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
	t_list		*map_list;
	int			lock;
	int			lock_valid_map_lines;
	int			lock_NEWS;

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

	t_texture	NO_data;
	t_texture	SO_data;
	t_texture	WE_data;
	t_texture	EA_data;
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

// MOVE PLAYER
void			move_player(t_game *game);
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_player *player);

// RAYCASTING
void			raycast_3d(t_game *game);
void			render_3d_map(t_game *game, t_texture texture, int column);
void			raycast_2d(t_game *game);

// RAYCASTING -> CHECK INTERSECTIONS
void			check_intersections(t_game *game, double angle, int x);
void			vertical_intersection(t_game *game, double angle);
void			horizontal_intersection(t_game *game, double angle);
// RAYCASTING -> CHECK DIRECTION
bool			is_left(double angle);
bool			is_right(double angle);
bool			is_up(double angle);
bool			is_down(double angle);
// RAYCASTING -> CALCULATION
double			calc_dist(double x1, double y1, double x2, double y2);
double			puissance2(double val);
double			normalize_angle(double angle);

// UTILS
void			clear_map(t_game *game);
void			ft_put_pixel(int x, int y, int color, t_game *game);
int				is_a_wall(char **map, double x, double y);
t_texture		get_texture(t_game *game, double angle);

// NEW AJOUT KENNY
int init_structure(t_game *data);
int opening_parsing(t_game_info *data, char *str);
int	transforms_list_to_tab(t_game_info *data);
int	map_parsing(char *line, t_game_info *data);
int	textures_function(char **file, char *line, int i);
int	colors_function(int (*tab)[3], char *line);
int	rgbToInt(int r, int g, int b);
int	close_win(t_game *game);

#endif
