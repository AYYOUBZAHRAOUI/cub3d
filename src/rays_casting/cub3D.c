/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzahrao <ayzahrao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:38:22 by ybekach           #+#    #+#             */
/*   Updated: 2025/06/22 05:47:42 by ayzahrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_gaming(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_input(game);
	draw_background(game);
	draw_3d_walls(game);
}

void	set_player_pos(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.map[i][j] == 'N' || game->map.map[i][j] == 'S'
				|| game->map.map[i][j] == 'E' || game->map.map[i][j] == 'W')
			{
				game->player.x = j * TILE_SIZE + TILE_SIZE / 2;
				game->player.y = i * TILE_SIZE + TILE_SIZE / 2;
				game->player.fov = M_PI / 3;
				if (game->map.map[i][j] == 'S')
					game->player.angle = M_PI / 2;
				else if (game->map.map[i][j] == 'N')
					game->player.angle = 3 * M_PI / 2;
				else if (game->map.map[i][j] == 'W')
					game->player.angle = M_PI;
				else if (game->map.map[i][j] == 'E')
					game->player.angle = 0;
				game->map.map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

int	texture_error(t_game *game)
{
	if (!game->textures[0].tex || !game->textures[1].tex
		|| !game->textures[2].tex || !game->textures[3].tex)
	{
		perror("Error: Failed to load textures");
		return (1);
	}
	return (0);
}

/*
 * @brief Load textures from the map structure and convert them to images
 * @param game Pointer to the game structure containing map and textures
 * @return 0 on success, 1 on error
*/
int	load_textures(t_game *game)
{
	mlx_image_t	*img;

	game->textures[0].tex = mlx_load_png(game->map.no);
	game->textures[1].tex = mlx_load_png(game->map.so);
	game->textures[2].tex = mlx_load_png(game->map.we);
	game->textures[3].tex = mlx_load_png(game->map.ea);
	if (texture_error(game))
		return (0);
	img = mlx_texture_to_image(game->mlx, game->textures[0].tex);
	game->textures[0].img = img; 
	img = mlx_texture_to_image(game->mlx, game->textures[1].tex);
	game->textures[1].img = img;
	img = mlx_texture_to_image(game->mlx, game->textures[2].tex);
	game->textures[2].img = img;
	img = mlx_texture_to_image(game->mlx, game->textures[3].tex);
	game->textures[3].img = img;
	return (1);
}
