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

void	move_player_ws(t_game *game, double step, int dir)
{
	double	nx;
	double	ny;

	nx = game->player.x + cos(game->player.angle) * step * dir;
	ny = game->player.y + sin(game->player.angle) * step * dir;
	if (!is_wall_at(game, nx, ny))
	{
		game->player.x = nx;
		game->player.y = ny;
	}
}

void	move_player_ad(t_game *game, double step, int dir)
{
	double	nx;
	double	ny;

	nx = game->player.x + cos(game->player.angle + M_PI / 2) * step * dir;
	ny = game->player.y + sin(game->player.angle + M_PI / 2) * step * dir;
	if (!is_wall_at(game, nx, ny))
	{
		game->player.x = nx;
		game->player.y = ny;
	}
}

void	handle_input(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_player_ws(game, 5.0, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_player_ws(game, 5.0, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_player_ad(game, 5.0, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_player_ad(game, 5.0, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player.angle -= 0.05;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player.angle += 0.05;
}
