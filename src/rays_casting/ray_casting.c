/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybekach <ybekach@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:37:36 by ybekach           #+#    #+#             */
/*   Updated: 2025/06/21 21:42:45 by ybekach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_ray_pos(double *rx, double *ry, double angle, double step)
{
	*rx += cos(angle) * step;
	*ry += sin(angle) * step;
}

static void	determine_hit_side(t_ray *ray, double angle)
{
	double	x_offset;

	x_offset = fmod(ray->wall_hit_x, TILE_SIZE);
	if (fabs(x_offset - TILE_SIZE) < 1.0 || x_offset < 1.0)
	{
		ray->hit_vertical = 1;
		if (cos(angle) > 0)
			ray->tex_dir = 3;
		else
			ray->tex_dir = 2;
	}
	else
	{
		ray->hit_vertical = 0;
		if (sin(angle) > 0)
			ray->tex_dir = 0;
		else
			ray->tex_dir = 1;
	}
}

t_ray	cast_ray(t_game *game, double angle)
{
	t_ray	ray;
	double	step;
	double	rx;
	double	ry;

	step = 1.0;
	rx = game->player.x;
	ry = game->player.y;
	angle = normalize_angle(angle);
	while (!is_wall_at(game, rx, ry))
	{
		update_ray_pos(&rx, &ry, angle, step);
		// if (rx < 0 || ry < 0 || rx >= game->map.width * TILE_SIZE 
		// 	|| ry >= game->map.height * TILE_SIZE)
		// 	break ;
	}
	ray.wall_hit_x = rx;
	ray.wall_hit_y = ry;
	ray.dist = sqrt(pow(rx - game->player.x, 2) + pow(ry - game->player.y, 2));
	determine_hit_side(&ray, angle);
	return (ray);
}
