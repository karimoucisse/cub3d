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

void	render_3d_map(t_game *game, t_texture texture, int x)
{
	double	wall_top_pixel;
	double	wall_bottom_pixel;
	int		y;
	int		texture_offset_x;
	int		distanceFromTop;
	int		texture_offset_y;
	int		color;
	double	project_plane;

	project_plane = (WIDTH / 2) / tan(FOV / 2);
	game->raycast_info.wall_height = (TILE / game->raycast_info.wall_hit_dist)
		* project_plane;
	wall_top_pixel = (HEIGHT / 2) - (game->raycast_info.wall_height / 2);
	if (wall_top_pixel < 0)
		wall_top_pixel = 0;
	wall_bottom_pixel = (HEIGHT / 2) + (game->raycast_info.wall_height / 2);
	if (wall_bottom_pixel > HEIGHT)
		wall_bottom_pixel = HEIGHT;
	y = 0;
	// ceilling color
	while (y < wall_top_pixel)
	{
		ft_put_pixel(x, y, 0xFFF000, game);
		y++;
	}
	if (game->raycast_info.was_hit_vertical)
		texture_offset_x = (int)game->raycast_info.wall_hity % TILE;
	else
		texture_offset_x = (int)game->raycast_info.wall_hitx % TILE;
	y = wall_top_pixel;
	// render texture wall
	while (y < wall_bottom_pixel)
	{
		distanceFromTop = y + (game->raycast_info.wall_height / 2) - (HEIGHT
				/ 2);
		texture_offset_y = distanceFromTop * ((double)texture.height
				/ game->raycast_info.wall_height);
		color = texture.pixels[(texture.width * texture_offset_y)
			+ texture_offset_x];
		ft_put_pixel(x, y, color, game);
		y++;
	}
	y = wall_bottom_pixel;
	// floor color
	while (y < HEIGHT)
	{
		ft_put_pixel(x, y, 0x00FFF0, game);
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
