/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybekach <ybekach@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:38:22 by ybekach           #+#    #+#             */
/*   Updated: 2025/06/21 19:58:36 by ybekach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_gaming(void *param)
{
    t_game    *game;

    game = (t_game *)param;
    handle_input(game);
    draw_background(game);
    draw_3d_walls(game);
}

void    set_player_pos(t_game *game)
{
    int    i;
    int    j;

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
                game->player.fov = M_PI / 3; // Initialize fov
                if (game->map.map[i][j] == 'S')
                    game->player.angle = M_PI / 2;
                else if (game->map.map[i][j] == 'N')
                    game->player.angle = 3 * M_PI / 2;
                else if (game->map.map[i][j] == 'W')
                    game->player.angle = M_PI;
                else if (game->map.map[i][j] == 'E')
                    game->player.angle = 0;
                game->map.map[i][j] = '0';
                return;
            }
            j++;
        }
        i++;
    }
}

void    load_textures(t_game *game)
{
    game->textures[0].tex = mlx_load_png(game->map.no);
    game->textures[1].tex = mlx_load_png(game->map.so);
    game->textures[2].tex = mlx_load_png(game->map.we);
    game->textures[3].tex = mlx_load_png(game->map.ea);
    game->textures[0].img = mlx_texture_to_image(game->mlx, game->textures[0].tex);
    game->textures[1].img = mlx_texture_to_image(game->mlx, game->textures[1].tex);
    game->textures[2].img = mlx_texture_to_image(game->mlx, game->textures[2].tex);
    game->textures[3].img = mlx_texture_to_image(game->mlx, game->textures[3].tex);
}

int    calculate_map_dimensions(t_game *game)
{
    int    i;
    int    width;

    i = 0;
    while (game->map.map[i])
        i++;
    game->map.height = i;
    width = ft_strlen(game->map.map[0]);
    game->map.width = width;
    return (0);
}
