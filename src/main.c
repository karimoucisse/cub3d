#include "cub3d.h"

void	init_game(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->mlx_ptr = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "Game");
	game->img_ptr = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	game->addr = mlx_get_data_addr(game->img_ptr, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	game->player.key_up = False;
	game->player.key_down = False;
	game->player.key_left = False;
	game->player.key_right = False;
	game->player.left_rotate = False;
	game->player.right_rotate = False;
	// game->player.radius;
	game->player.turn_dir = 0;
	game->player.walk_dir = 0;
	while (game->game_info->map[i])
	{
		j = 0;
		while (game->game_info->map[i][j])
		{
			if (ft_strchr("NWES", game->game_info->map[i][j]))
			{
				game->player.x = j * TILE + TILE / 2;
				game->player.y = i * TILE + TILE / 2;
			}
			if (game->game_info->map[i][j] == 'N')
				game->player.rot_angle = N;
			if (game->game_info->map[i][j] == 'S')
				game->player.rot_angle = S;
			if (game->game_info->map[i][j] == 'E')
				game->player.rot_angle = E;
			if (game->game_info->map[i][j] == 'W')
				game->player.rot_angle = W;
			j++;
		}
		i++;
	}
}

int	is_a_wall(char **map, double x, double y)
{
	int	x_block;
	int	y_block;

	x_block = floor(x / TILE);
	y_block = floor(y / TILE);
	if (!map[y_block] || !map[y_block][x_block] || (map[y_block][x_block] != '1'
			&& map[y_block][x_block] != ' '))
		return (0);
	return (1);
}

int	key_press(int keycode, t_player *player)
{
	if (keycode == T)
		player->key_up = true;
	if (keycode == B)
		player->key_down = true;
	if (keycode == L)
		player->key_left = true;
	if (keycode == R)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rotate = true;
	if (keycode == RIGHT)
		player->right_rotate = true;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == T)
		player->key_up = false;
	if (keycode == B)
		player->key_down = false;
	if (keycode == L)
		player->key_left = false;
	if (keycode == R)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}
void	ft_put_pixel(int x, int y, int color, t_game *game)
{
	char	*pxl;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pxl = game->addr + (y * game->line_length + x * (game->bits_per_pixel
					/ 8));
		*(unsigned int *)pxl = color;
	}
}

void	draw_square(int x, int y, int color, int size, t_game *game)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_put_pixel(x + i, y, color, game);
		ft_put_pixel(x + i, y + size, color, game);
		ft_put_pixel(x, y + i, color, game);
		ft_put_pixel(x + size, y + i, color, game);
		i++;
	}
}
void	create_map(t_game *game)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	map = game->game_info->map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_square(j * TILE, i * TILE, 0x00FF00, TILE, game);
			j++;
		}
		i++;
	}
}

void	move_player(t_game *game)
{
	double	mv_speed;
	char	**map;
	double	rot_speed;
	double	x_cpy;
	double	y_cpy;

	rot_speed = 0.002;
	map = game->game_info->map;
	mv_speed = 0.2;
	x_cpy = game->player.x;
	y_cpy = game->player.y;
	if (game->player.left_rotate)
		game->player.rot_angle -= rot_speed;
	if (game->player.right_rotate)
		game->player.rot_angle += rot_speed;
	if (game->player.key_up)
	{
		x_cpy = game->player.x + cos(game->player.rot_angle) * mv_speed;
		y_cpy = game->player.y + sin(game->player.rot_angle) * mv_speed;
	}
	if (game->player.key_down)
	{
		x_cpy -= cos(game->player.rot_angle) * mv_speed;
		y_cpy -= sin(game->player.rot_angle) * mv_speed;
	}
	if (!is_a_wall(map, x_cpy, y_cpy))
	{
		game->player.x = x_cpy;
		game->player.y = y_cpy;
	}
}

void	clear_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			ft_put_pixel(j, i, 0, game);
			j++;
		}
		i++;
	}
}

void	draw_ray(t_game *game, double angle)
{
	int		i;
	double	x;
	double	y;

	i = 0;
	x = (game->player.x + 5) + cos(angle) * i;
	y = (game->player.y + 5) + sin(angle) * i;
	while (1)
	{
		x = (game->player.x) + cos(angle) * i;
		y = (game->player.y) + sin(angle) * i;
		if (is_a_wall(game->game_info->map, x - 0.2, y - 0.2)
			|| is_a_wall(game->game_info->map, x + 0.2, y + 0.2))
			break ;
		if (is_a_wall(game->game_info->map, x, y))
			break ;
		i++;
		ft_put_pixel(x, y, 0x00FFF0, game);
	}
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}

double	puissance2(double val)
{
	return (val * val);
}

double	calc_dist(double x1, double y1, double x2, double y2)
{
	return (sqrt(puissance2(x2 - x1) + puissance2(y2 - y1)));
}

bool	is_down(double angle)
{
	if (angle > 0 && angle < PI)
		return (true);
	return (false);
}
bool	is_up(double angle)
{
	if (!is_down(angle))
		return (true);
	return (false);
}
bool	is_right(double angle)
{
	if (angle < (0.5 * PI) || angle > (1.5 * PI))
		return (true);
	return (false);
}
bool	is_left(double angle)
{
	if (!is_right(angle))
		return (true);
	return (false);
}

void	h_intersection(t_game *game, double angle)
{
	double	xstep;
	double	ystep;
	double	xa;
	double	ya;
	double	nxt_xstep;
	double	nxt_ystep;
	bool	hit_wall;
	double	hit_x;
	double	hit_y;
	double	verif;

	hit_wall = false;
	ya = floor(game->player.y / TILE) * TILE;
	if (is_down(angle))
		ya += TILE;
	xa = game->player.x + ((ya - game->player.y) / tan(angle));
	ystep = TILE;
	if (is_up(angle))
		ystep *= -1;
	xstep = TILE / tan(angle);
	if (is_left(angle) && xstep > 0)
		xstep *= -1;
	if (is_right(angle) && xstep < 0)
		xstep *= -1;
	nxt_xstep = xa;
	nxt_ystep = ya;
	verif = nxt_ystep;
	while (nxt_xstep >= 0 && (int)floor(nxt_xstep / TILE) <= 25
		&& nxt_ystep >= 0 && (int)floor(nxt_ystep / TILE) <= 9)
	{
		if (is_up(angle))
			verif = nxt_ystep - 1;
		else
			verif = nxt_ystep;
		if (is_a_wall(game->game_info->map, nxt_xstep, verif))
		{
			hit_wall = true;
			hit_x = nxt_xstep;
			hit_y = nxt_ystep;
			break ;
		}
		else
		{
			nxt_xstep += xstep;
			nxt_ystep += ystep;
		}
	}
	if (hit_wall)
	{
		game->raycast_info.h_hit_posx = hit_x;
		game->raycast_info.h_hit_posy = hit_y;
		game->raycast_info.h_hit_dist = calc_dist(game->player.x,
				game->player.y, hit_x, hit_y);
		game->raycast_info.was_hit_vertical = false;
	}
	else
		game->raycast_info.h_hit_dist = __INT_MAX__;
}

void	v_intersection(t_game *game, double angle)
{
	double	xstep;
	double	ystep;
	double	xa;
	double	ya;
	double	nxt_xstep;
	double	nxt_ystep;
	bool	hit_wall;
	double	hit_x;
	double	hit_y;
	double	verif;

	hit_wall = false;
	xa = floor(game->player.x / TILE) * TILE;
	if (is_right(angle))
		xa += TILE;
	ya = game->player.y + ((xa - game->player.x) * tan(angle));
	xstep = TILE;
	if (is_left(angle))
		xstep *= -1;
	ystep = TILE * tan(angle);
	if (is_up(angle) && ystep > 0)
		ystep *= -1;
	if (is_down(angle) && ystep < 0)
		ystep *= -1;
	nxt_xstep = xa;
	nxt_ystep = ya;
	verif = nxt_xstep;
	hit_x = 0;
	hit_y = 0;
	while (nxt_xstep >= 0 && (int)floor(nxt_xstep / TILE) <= 25
		&& nxt_ystep >= 0 && (int)floor(nxt_ystep / TILE) <= 9)
	{
		if (is_left(angle))
			verif = nxt_xstep - 1;
		else
			verif = nxt_xstep;
		if (is_a_wall(game->game_info->map, verif, nxt_ystep))
		{
			hit_wall = true;
			hit_x = nxt_xstep;
			hit_y = nxt_ystep;
			break ;
		}
		else
		{
			nxt_xstep += xstep;
			nxt_ystep += ystep;
		}
	}
	if (hit_wall)
	{
		game->raycast_info.v_hit_posx = hit_x;
		game->raycast_info.v_hit_posy = hit_y;
		game->raycast_info.v_hit_dist = calc_dist(game->player.x,
				game->player.y, hit_x, hit_y);
		game->raycast_info.was_hit_vertical = true;
	}
	else
		game->raycast_info.v_hit_dist = __INT_MAX__;
}

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

void	render_3d_map(t_game *game)
{
	double	project_plane;

	project_plane = (WIDTH / 2) / tan(FOV / 2);
	game->raycast_info.wall_height = (TILE / game->raycast_info.wall_hit_dist)
		* project_plane;
	// draw_vertical_line(game);
	// printf("h = %lf\n", game->raycast_info.wall_height);
}
void	intersections(t_game *game, double angle)
{
	h_intersection(game, angle);
	v_intersection(game, angle);
	if (game->raycast_info.v_hit_dist < game->raycast_info.h_hit_dist)
	{
		game->raycast_info.wall_hit_dist = game->raycast_info.v_hit_dist * cos(angle - game->player.rot_angle);
		game->raycast_info.wall_hitx = game->raycast_info.v_hit_posx;
		game->raycast_info.wall_hity = game->raycast_info.v_hit_posy;
	}
	else
	{
		game->raycast_info.wall_hit_dist = game->raycast_info.h_hit_dist * cos(angle - game->player.rot_angle);
		game->raycast_info.wall_hitx = game->raycast_info.h_hit_posx;
		game->raycast_info.wall_hity = game->raycast_info.h_hit_posy;
	}
	// Déterminer la face du mur touchée
	if (game->raycast_info.v_hit_dist > game->raycast_info.h_hit_dist)
	// Si l'intersection horizontale est la plus proche
	{
		if (sin(angle) > 0)
			game->raycast_info.color = 0xFF0000;
		else
			game->raycast_info.color = 0x00FF00;
	}
	else // Sinon, l'intersection verticale est la plus proche
	{
		if (cos(angle) > 0)
			game->raycast_info.color = 0x0000FF;
		else
			game->raycast_info.color = 0xFFA500;
	}
	render_3d_map(game);
}

void	raycast_2d(t_game *game)
{
	int		i;
	double	angle;

	move_player(game);
	clear_map(game);
	create_map(game);
	draw_square(game->player.x, game->player.y, 0x00FFF0, 10, game);
	i = 0;
	angle = game->player.rot_angle - (FOV / 2);
	while (i < WIDTH)
	{
		// intersections(game, normalize_angle(angle));
		draw_ray(game, angle);
		angle += FOV / WIDTH;
		i++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->img_ptr, 0, 0);
}

void	raycast_3d(t_game *game)
{
	int		i;
	double	angle;

	move_player(game);
	clear_map(game);
	// create_map(game);
	// draw_square(game->player.x, game->player.y, 0x00FFF0, 10, game);
	i = 0;
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->img_ptr, 0, 0);
	angle = game->player.rot_angle - (FOV / 2);
	while (i < WIDTH)
	{
		// draw_ray(game, angle);
		intersections(game, normalize_angle(angle));
		draw_vertical_line(game, i, angle);
		angle += FOV / WIDTH;
		i++;
	}
}

int	start_game(t_game *game)
{
	// raycast_2d(game);
	raycast_3d(game);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (EXIT_FAILURE);
	if (!check_file_name(av[1]))
		printf("Error\n");
	game.game_info = parse_file(av[1]);
	init_game(&game);
	mlx_hook(game.mlx_win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.mlx_win, 3, 1L << 1, key_release, &game.player);
	mlx_loop_hook(game.mlx_ptr, start_game, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
