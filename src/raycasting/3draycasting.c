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

void	render_3d_map(t_game *game, int i, double angle)
{
	double	project_plane;

	project_plane = (WIDTH / 2) / tan(FOV / 2);
	game->raycast_info.wall_height = (TILE / game->raycast_info.wall_hit_dist)
		* project_plane;
	draw_vertical_line(game, i, angle);
}
void	raycast_3d(t_game *game)
{
	int		i;
	double	angle;

	move_player(game);
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->img_ptr, 0, 0);
	i = 0;
	angle = game->player.rot_angle - (FOV / 2);
	while (i < WIDTH)
	{
		check_intersections(game, normalize_angle(angle));
		render_3d_map(game, i, angle);
		angle += FOV / WIDTH;
		i++;
	}
}
