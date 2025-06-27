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
	int		ceiling_color;
	int		floor_color;

	ceiling_color = (game->map.c->red << 24) 
		| (game->map.c->green << 16) | (game->map.c->blue << 8) 
		| 0xFF;
	floor_color = (game->map.f->red << 24) 
		| (game->map.f->green << 16) | (game->map.f->blue << 8) 
		| 0xFF;
	draw_ceiling_and_floor(game, ceiling_color, floor_color);
}

static int	get_tx(t_ray *r, mlx_texture_t *t)
{
	int	tx;

	if (r->hit_vertical)
		tx = (int)fmod(r->wall_hit_y, TILE_SIZE);
	else
		tx = (int)fmod(r->wall_hit_x, TILE_SIZE);
	return ((tx * t->width) / TILE_SIZE);
}

// static void	draw_column(t_game *g, t_ray *r, int x, double wh)
// {
// 	int				
// 	int				y;
// 	int				ty;
// 	int				s;
// 	mlx_texture_t	*t;

// 	t = g->textures[r->tex_dir].tex;
// 	s = (HEIGHT / 2) - (wh / 2);
// 	y = s;
// 	while (y < s + wh)
// 	{
// 		if (y >= 0 && y < HEIGHT)
// 		{
// 			ty = ((y - s) * t->height) / wh;
// 			if ((unsigned)ty < t->height)
// 				mlx_put_pixel(g->img, x,
// 					y, *(uint32_t *)
// 					&t->pixels[4 * 
// 					(ty * t->width + get_tx(r, t))]);
// 		}
// 		y++;
// 	}
// }

static void	draw_column(t_game *g, t_ray *r, int x, double wh)
{
	int				index;
	int				y;
	int				ty;
	int				s;
	mlx_texture_t	*t;

	t = g->textures[r->tex_dir].tex;
	s = (HEIGHT / 2) - (wh / 2);
	y = s;
	while (y < s + wh)
	{
		if (y >= 0 && y < HEIGHT)
		{
			ty = ((y - s) * t->height) / wh;
			index = 4 * (ty * t->width + get_tx(r, t));
			if ((unsigned)ty < t->height)
				mlx_put_pixel(g->img, x, y, *(uint32_t *)&t->pixels[index]);
		}
		y++;
	}
}

void	draw_3d_walls(t_game *g)
{
	int		i;
	t_ray	r;
	double	a;
	double	d;

	i = 0;
	while (i < NUM_RAYS)
	{
		a = g->player.angle - (g->player.fov / 2)
			+ ((double)i / WIDTH) * g->player.fov;
		r = cast_ray(g, a);
		d = r.dist * cos(a - g->player.angle);
		draw_column(g, &r, i, (TILE_SIZE * HEIGHT) / d);
		i++;
	}
}
