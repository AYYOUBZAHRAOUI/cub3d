/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzahrao <ayzahrao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:37:04 by ybekach           #+#    #+#             */
/*   Updated: 2025/06/22 05:49:52 by ayzahrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall_at(t_game *game, double x, double y)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)(x / TILE_SIZE);
	grid_y = (int)(y / TILE_SIZE);
	if (grid_x < 0 || grid_y < 0 || grid_y >= game->map.height 
		|| grid_x >= game->map.width)
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
