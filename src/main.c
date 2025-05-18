/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzahrao <ayzahrao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:51:13 by ayzahrao          #+#    #+#             */
/*   Updated: 2025/05/18 01:20:21 by ayzahrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	i need a function to check leak memory
*/
void	check_leak(void)
{
	system("leaks -q cub3D");
}

void player_position(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (game->map.map[x])
	{
		y = 0;
		while (game->map.map[x][y])
		{
			if (game->map.map[x][y] == 'W' || 
				game->map.map[x][y] == 'E' ||
				game->map.map[x][y] == 'N' ||
				game->map.map[x][y] == 'S')
			{
				game->player.x = x * TILE_SIZE + TILE_SIZE / 2; // need more for this 
				game->player.y = y * TILE_SIZE + TILE_SIZE / 2; // need more for this
				if (game->map.map[x][y] == 'W')
					game->player.angle = M_PI;
				else if (game->map.map[x][y] == 'E')
					game->player.angle = 0;
				else if (game->map.map[x][y] == 'N')
					game->player.angle = -M_PI / 2;
				else if (game->map.map[x][y] == 'S')
					game->player.angle = M_PI / 2;
				return ;
			}
			y++;
		}
		x++;
	}
}
// static void ft_hook(void* param)
// {
// 	const mlx_t* mlx = param;

// 	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
// }


int	main(int ac, char **av)
{
	t_game game;
	
	// parsing
	if (check_args(ac, av) == 0)
		return (1);
	int_map(&(game.map));
	if (!(parse_map(av[1], &(game.map))))
		return (free_map(&(game.map)), 1);
	print_map(&(game.map));
	printf("map:\n");
	// next
	game.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!game.mlx)
		perror("Error");
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	if (!game.img || (mlx_image_to_window(game.mlx, game.img, 0, 0) < 0))
		perror("Error");
	player_position(&game);
	mlx_loop_hook(game.mlx, update, &game);
	mlx_loop(game.mlx);
	// mlx_terminate(game.mlx);
	return (0);
}


	
	
	

	// /* Do stuff */

	// // Create and display the image.
	// mlx_image_t* img = mlx_new_image(mlx, 256, 256);
	// if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
	// 	ft_error();

	// // Even after the image is being displayed, we can still modify the buffer.
	// mlx_put_pixel(img, 0, 0, 0xFF0000FF);

	// // Register a hook and pass mlx as an optional param.
	// // NOTE: Do this before calling mlx_loop!
	// mlx_loop_hook(mlx, ft_hook, mlx);
	// mlx_loop(mlx);
	// mlx_terminate(mlx);
	// return (EXIT_SUCCESS);