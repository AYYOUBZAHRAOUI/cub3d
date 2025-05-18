/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzahrao <ayzahrao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:35:19 by ybekach           #+#    #+#             */
/*   Updated: 2025/05/18 01:02:05 by ayzahrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calculate_wall_height(t_game *game, int i)
{
	double	ray_angle;
	double	dist;
	double	wall_height;

	ray_angle = game->player.angle - (FOV / 2) + (i * FOV / NUM_RAYS);
	printf("cast_ray: %f, ray_angle: %f\n", cast_ray(game, ray_angle), ray_angle);
	dist = cast_ray(game, ray_angle) * cos(ray_angle - game->player.angle);
	wall_height = (TILE_SIZE * HEIGHT) / dist;
	return (wall_height);
}

void	draw_3d_walls(t_game *game)
{
	int		y;
	int		i;
	int		end;
	int		start;
	double	wall_height;

	i = 0;
	while (i < NUM_RAYS)
	{
		wall_height = calculate_wall_height(game, i);
		start = (HEIGHT / 2) - (wall_height / 2);
		end = start + wall_height;
		printf("start: %d, end: %d wall_height: %f\n", start, end, wall_height);
		y = start;
		while (y < end)
		{
			if (y >= 0 && y < HEIGHT)
				mlx_put_pixel(game->img, i, y, 0xFFA52A2A);
			y++;
		}
		i++;
	}
}

void	update(void *param)
{
	int		x;
	int		y;
	t_game	*game;

	game = (t_game *)param;
	handle_input(game);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(game->img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
	draw_3d_walls(game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}
