#include "cub3d.h"

void	draw_vertical_line(t_game *game, int x, double angle)
{
	int		i;
	double	y;
	double	height;

	height = game->raycast_info.wall_height;
	y = (HEIGHT / 2) - (height / 2);
	i = 0;
	while (i < height)
	{
		ft_put_pixel(x, y + i, game->raycast_info.color, game);
		i++;
	}
}

// void	render_3d_map(t_game *game, int i, double angle)
// {
// 	double	project_plane;

// 	project_plane = (WIDTH / 2) / tan(FOV / 2);
// 	game->raycast_info.wall_height = (TILE / game->raycast_info.wall_hit_dist)
// 		* project_plane;
// 	draw_vertical_line(game, i, angle);
// }

void	render_3d_map(t_game *game, t_texture texture, int x)
{
	int		y;
	int		texture_pos_initial;
	int		texture_y;
	int		color;
	double	step;
	double	compteur;
	double	project_plane;
	double	wall_start;

	project_plane = (WIDTH / 2) / tan(FOV / 2);
	game->raycast_info.wall_height = (TILE / game->raycast_info.wall_hit_dist)
		* project_plane;
	if (!game->raycast_info.was_hit_vertical)
		texture_pos_initial = (int)((int)game->raycast_info.wall_hitx % TILE)
			* texture.width / TILE;
	else
		texture_pos_initial = (int)((int)game->raycast_info.wall_hity % TILE)
			* texture.width / TILE;
	step = (double)texture.height / game->raycast_info.wall_height;
	wall_start = (HEIGHT / 2) - (game->raycast_info.wall_height / 2);
	compteur = (wall_start < 0) ? (-wall_start * step) : 0.0;
	y = 0;
	while (y < HEIGHT)
	{
		if (y > (HEIGHT / 2) - (game->raycast_info.wall_height / 2)
			&& y < (HEIGHT / 2) + (game->raycast_info.wall_height / 2))
		{
			texture_y = (int)compteur % texture.height;
			compteur += step;
			color = texture.pixels[texture_y * texture.width
				+ texture_pos_initial];
		}
		else
		{
			if (y < (HEIGHT / 2))
				color = 0x00FFF0;
			else
				color = 0xFFF000;
		}
		ft_put_pixel(x, y, color, game);
		y++;
	}
}

float	get_xcord(t_game *game, t_texture texture)
{
	if (game->raycast_info.was_hit_vertical)
	{
		return (fmodf(game->raycast_info.wall_hity * (texture.width / TILE),
				texture.width));
	}
	return (fmodf(game->raycast_info.wall_hitx * (texture.width / TILE),
			texture.width));
}

// void	render_3d_map(t_game *game, t_texture texture, int x)
// {
// 	double	wall_top_pixel;
// 	double	wall_bottom_pixel;
// 	int32_t	*img_px;
// 	double	offset;
// 	float	xcord;
// 	float	ycord;

// 	img_px = (int32_t *)texture.pixels;
// 	wall_top_pixel = (HEIGHT / 2) - (game->raycast_info.wall_height / 2);
// 	wall_bottom_pixel = (HEIGHT / 2) + (game->raycast_info.wall_height / 2);
// 	if (wall_top_pixel < 0)
// 		wall_top_pixel = 0;
// 	if (wall_bottom_pixel > HEIGHT)
// 		wall_bottom_pixel = HEIGHT;
// 	offset = texture.height / game->raycast_info.wall_height;
// 	xcord = get_xcord(game, texture);
// 	ycord = (wall_top_pixel - (HEIGHT / 2.0) + (game->raycast_info.wall_height
// 				/ 2)) * offset;
// 	if (ycord < 0)
// 		ycord = 0;
// 	while (y < HEIGHT)
// 	{
// 	}
// }

void	raycast_3d(t_game *game)
{
	int		i;
	double	angle;

	move_player(game);
	i = 0;
	angle = game->player.rot_angle - (FOV / 2);
	while (i < WIDTH)
	{
		check_intersections(game, normalize_angle(angle), i);
		// render_3d_map(game, i, angle);
		// render_3d_map(game, texture);
		angle += FOV / WIDTH;
		i++;
	}
	// clear_map(game);
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->img_ptr, 0, 0);
}
