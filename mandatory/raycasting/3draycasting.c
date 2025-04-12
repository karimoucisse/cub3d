#include "cub3d.h"

int	get_xcord(t_game *game)
{
	int	texture_offset_x;

	if (game->raycast_info.was_hit_vertical)
		texture_offset_x = (int)game->raycast_info.wall_hity % TILE;
	else
		texture_offset_x = (int)game->raycast_info.wall_hitx % TILE;
	return (texture_offset_x);
}

void	render_3d_map(t_game *game, t_texture texture, int x)
{
	int		y;
	int		texture_offset_x;
	int		texture_offset_y;
	int		distanceFromTop;
	int		color;
	double	project_plane;
	double	wall_top_pixel;
	double	wall_bottom_pixel;

	project_plane = (WIDTH / 2) / tan(FOV / 2);
	game->raycast_info.wall_height = (TILE / game->raycast_info.wall_hit_dist)
		* project_plane;
	wall_top_pixel = (HEIGHT / 2) - (game->raycast_info.wall_height / 2);
	if (wall_top_pixel < 0)
		wall_top_pixel = 0;
	wall_bottom_pixel = (HEIGHT / 2) + (game->raycast_info.wall_height / 2);
	if (wall_bottom_pixel > HEIGHT)
		wall_bottom_pixel = HEIGHT;
	texture_offset_x = get_xcord(game);
	y = 0;
	while (y < wall_top_pixel)
	{
		color = rgbToInt(game->game_info->ceiling_color[0], game->game_info->ceiling_color[1], game->game_info->ceiling_color[2]);
		ft_put_pixel(x, y, color, game);
		y++;
	}
	y = wall_top_pixel;
	while (y < wall_bottom_pixel)
	{
		distanceFromTop = y + (game->raycast_info.wall_height / 2) - (HEIGHT
				/ 2);
		texture_offset_y = distanceFromTop * ((float)texture.height
				/ game->raycast_info.wall_height);
		color = texture.pixels[(texture.width * texture_offset_y)
			+ texture_offset_x];
		ft_put_pixel(x, y, color, game);
		y++;
	}
	y = wall_bottom_pixel;
	while (y < HEIGHT)
	{
		color = rgbToInt(game->game_info->floor_color[0], game->game_info->floor_color[1], game->game_info->floor_color[2]);
		ft_put_pixel(x, y, color, game);
		y++;
	}
}

void	raycast_3d(t_game *game)
{
	int		i;
	double	angle;
	// t_texture texture;
	move_player(game);
	i = 0;
	angle = game->player.rot_angle - (FOV / 2);
	while (i < WIDTH)
	{
		check_intersections(game, normalize_angle(angle), i);
		// texture = get_texture(game, i);
		// render_3d_map(game, texture, i);
		angle += FOV / WIDTH;
		i++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->img_ptr, 0, 0);
}
