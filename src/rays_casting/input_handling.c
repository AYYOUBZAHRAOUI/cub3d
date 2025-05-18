/* ************************************************************************** */
/*	                                                                          */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybekach <ybekach@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:36:48 by ybekach           #+#    #+#             */
/*   Updated: 2025/05/13 13:40:45 by ybekach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_game *game, double move_step, int direction)
{
	double	ny ;
	double	nx; 

	nx = game->player.x + cos(game->player.angle) * move_step * direction;
	ny = game->player.y + sin(game->player.angle) * move_step * direction;
	if (!is_wall_at(game, nx, ny))
	{
		game->player.x = nx;
		game->player.y = ny;
	}
}

void	handle_input(t_game *game)
{
	double	move_step;

	move_step = 5.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_player(game, 5.0, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_player(game, 5.0, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		game->player.angle -= 0.05;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		game->player.angle += 0.05;
}
