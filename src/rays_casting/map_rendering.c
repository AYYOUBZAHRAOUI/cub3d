/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   map_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzahrao <ayzahrao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:35:19 by ybekach           #+#    #+#             */
/*   Updated: 2025/06/22 05:52:03 by ayzahrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling_and_floor(t_game *game, int ceiling_color, int floor_color)
{
	int		x;
	int		y;

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(game->img, x, y, ceiling_color);
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(game->img, x, y, floor_color);
			x++;
		}
		y++;
	}
}

void	draw_background(t_game *game)
{
	int	ceiling_color;
	int	floor_color;

	ceiling_color = (game->map.c->red << 24) 
		| (game->map.c->green << 16) | (game->map.c->blue << 8) 
		| 0xFF;
	floor_color = (game->map.f->red << 24) 
		| (game->map.f->green << 16) | (game->map.f->blue << 8) 
		| 0xFF;
	draw_ceiling_and_floor(game, ceiling_color, floor_color);
}

void	draw_3d_walls(t_game *game)
{
	int			i;
	t_ray		ray;
	double		ray_angle;
	double		dist;
	double		wall_h;
	int			start;
	int			end;
	int			y;
	int			tx;
	int			ty;
	uint32_t	color;
	mlx_texture_t	*tex;

	i = 0;
	while (i < NUM_RAYS)
	{
		ray_angle = game->player.angle - (game->player.fov / 2)
			+ ((double)i / WIDTH) * game->player.fov;
		ray = cast_ray(game, ray_angle);
		dist = ray.dist * cos(ray_angle - game->player.angle);
		wall_h = (TILE_SIZE * HEIGHT) / dist;
		start = (HEIGHT / 2) - (wall_h / 2);
		end = start + wall_h;
		if (ray.hit_vertical)
			tx = (int)fmod(ray.wall_hit_y, TILE_SIZE);
		else
			tx = (int)fmod(ray.wall_hit_x, TILE_SIZE);
		tex = game->textures[ray.tex_dir].tex;
		tx = (tx * tex->width) / TILE_SIZE;
		y = start;
		while (y < end)
		{
			if (y >= 0 && y < HEIGHT)
			{
				ty = ((y - start) * tex->height) / wall_h;
				if ((uint32_t)tx < tex->width && (uint32_t)ty < tex->height)
				{
					color = *(uint32_t *)&tex->pixels[4 * (ty * tex->width + tx)];
					mlx_put_pixel(game->img, i, y, color);
				}
			}
			y++;
		}
		i++;
	}
}
