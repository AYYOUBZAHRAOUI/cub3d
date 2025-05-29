/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzahrao <ayzahrao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:37:36 by ybekach           #+#    #+#             */
/*   Updated: 2025/05/22 15:11:35 by ayzahrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall_at(t_game *game, double x, double y)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)((x - TILE_SIZE / 2)   / TILE_SIZE);
	grid_y = (int)((y - TILE_SIZE / 2) / TILE_SIZE);
	if (grid_x < 0 || grid_y < 0)
		return (1);
	return (game->map.map[grid_y][grid_x] == '1');
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

double	cast_ray(t_game *game, double ray_angle)
{
	double	ray_x;
	double	ray_y;
	double	step_size;

	ray_angle = normalize_angle(ray_angle);
	ray_x = game->player.x;
	ray_y = game->player.y;
	step_size = 1.0;
	while (!is_wall_at(game, ray_x, ray_y))
	{
		ray_x += cos(ray_angle) * step_size;
		ray_y += sin(ray_angle) * step_size;
	}
	return (sqrt((ray_x - game->player.x) * (ray_x - game->player.x)
			+ (ray_y - game->player.y) * (ray_y - game->player.y)));
}
