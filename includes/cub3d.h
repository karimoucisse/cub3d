/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:47:18 by kcisse            #+#    #+#             */
/*   Updated: 2025/04/18 13:47:35 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>

# define HIT_DOOR 2
# define SUCCESS 0
# define ERROR 1
# define PI 3.14159265359
# define MAX_MAP_SIZE 100
# define WIDTH 980
# define HEIGHT 620
# define TILE 64
# define MINIMAP_TILE 10
# define FOV 60
# define MOVE_SPEED 0.5
# define SPRINT 1.2
# define ROTATION_SPEED 0.010
# define FAST_ROTATION 0.020
# define COLLISION_OFFSET 20
# define T 119 // w
# define B 115 // s
# define L 97  // a
# define R 100 // d
# define LEFT 65361
# define RIGHT 65363
# define ECHAP 65307
# define CTRL 65507

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
	int			hit_type_vertical;
	int			hit_type_horizontal;
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
	bool		key_up;
	bool		key_down;
	bool		key_left;
	bool		key_right;

	bool		left_rotate;
	bool		right_rotate;

	double		radius;
	int			turn_dir;
	int			walk_dir;
	bool		sprint;
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
	char		*door_texture;
	int			floor_color[3];
	int			ceiling_color[3];
	char		**map;
	t_list		*map_list;
	int			map_height;
	int			map_widht;
	int			lock;
	int			lock_valid_map_lines;
	int			lock_news;

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

	t_texture	no_data;
	t_texture	so_data;
	t_texture	we_data;
	t_texture	ea_data;
	t_texture	do_data;
}				t_game;

// PARSING
//		FILE
int				check_file_name(char *file_name);

// MOVE PLAYER
void			move_player(t_game *game);
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_player *player);

// RAYCASTING
void			raycast_3d(t_game *game);
void			render_map(t_game *game, t_texture texture, int column);
void			minimap(t_game *game);

// RAYCASTING -> CHECK INTERSECTIONS
void			check_intersections(t_game *game, double angle, int x);
void			check_intersections_bonus(t_game *game, double angle, int x,
					bool minimap);
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
int				get_xcord(t_game *game);
void			calc_ray_distance(t_game *game, double angle);

// UTILS
void			clear_map(t_game *game);
int				is_a_wall_bonus(t_game *game, double x, double y, int *door);
int				is_a_wall(t_game *game, double x, double y);

// NEW AJOUT KENNY
int				init_structure(t_game *data);
int				opening_parsing(t_game_info *data, char *str);
int				transforms_list_to_tab(t_game_info *data);
int				map_parsing(char *line, t_game_info *data);
int				textures_function(char **file, char *line, int i);
int				colors_function(int (*tab)[3], char *line);
int				rgb_to_int(int r, int g, int b);

// INIT 2
int				init_game(t_game *game);
int				init_textures(void *mlx, char *file, t_texture *img);

// HANDLE END
void			free_list(t_list *lst);
void			free_map(char **map);
void			free_structure(t_game *game);
int				close_win(t_game *game);

// PUT PIXELS
void			ft_put_pixel(int x, int y, int color, t_game *game);
double			put_ceiling_pixel(t_game *game, int x);
double			put_floor_pixel(t_game *game, int x);
void			put_wall_pixel(t_game *game, t_texture texture, int y, int x);

void			draw_ray(t_game *game, double angle);
int				mouse_move(int x, int y, t_game *game);
// DOOR
void			open_doors_in_radius(t_game *game, double radius);
#endif
