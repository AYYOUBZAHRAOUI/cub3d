/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzahrao <ayzahrao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:51:13 by ayzahrao          #+#    #+#             */
/*   Updated: 2025/06/22 05:56:27 by ayzahrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_leak(void)
{
	system("leaks -q cub3D");
}

int	main(int ac, char **av)
{
	t_game	game;

	if (check_args(ac, av) == 0)
		return (1);
	int_map(&(game.map));
	if (!(parse_map(av[1], &(game.map))))
		return (free_map(&(game.map)), 1);
	set_player_pos(&game);
	game.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!game.mlx)
		return (perror("Error"), free_map(&(game.map)), 1);
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	if (!game.img || 
		(mlx_image_to_window(game.mlx, game.img, 0, 0) < 0) 
		|| load_textures(&game) == 0)
		return (perror("Error"), free_map(&(game.map)), 
			mlx_terminate(game.mlx), 1);
	mlx_loop_hook(game.mlx, ft_gaming, &game);
	mlx_loop(game.mlx);
	return (free_map(&(game.map)), mlx_terminate(game.mlx), 0);
}
