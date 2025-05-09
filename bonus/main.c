/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knavarre <knavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:02:23 by knavarre          #+#    #+#             */
/*   Updated: 2025/04/17 15:54:14 by knavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	start_game(t_game *game)
{
	raycast_3d(game);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (EXIT_FAILURE);
	if (!check_file_name(av[1]))
		return (printf("Error\n"), ERROR);
	if (init_structure(&game) != SUCCESS)
		return (close_win(&game), ERROR);
	if (opening_parsing(game.game_info, av[1]) != SUCCESS)
		return (close_win(&game), ERROR);
	if (init_game(&game) != SUCCESS)
		return (close_win(&game), ERROR);
	mlx_hook(game.mlx_win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.mlx_win, 3, 1L << 1, key_release, &game.player);
	mlx_hook(game.mlx_win, 6, 1L << 6, mouse_move, &game);
	mlx_hook(game.mlx_win, 17, 0, close_win, &game);
	mlx_loop_hook(game.mlx_ptr, start_game, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
