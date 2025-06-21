// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ybekach <ybekach@student.1337.ma>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/05/16 10:23:01 by ybekach           #+#    #+#             */
// /*   Updated: 2025/06/21 19:10:28 by ybekach          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "cub3d.h"

// int    main(void)
// {
//     t_game    game;
//     int       i;

//     // Example map setup for testing (replace with your actual map loading logic)
//     game.map.map = malloc(11 * sizeof(char *)); // 10 rows + NULL terminator
//     if (!game.map.map)
//         return (1);
//     char *test_map[] = {
//         "1111111111",
//         "1000000001",
//         "1000000001",
//         "1000000001",
//         "1000010001",
//         "10000N0001",
//         "1000000001",
//         "1000000001",
//         "1000000001",
//         "1111111111",
//         NULL
//     };
//     for (i = 0; i < 11; i++)
//     {
//         game.map.map[i] = test_map[i] ? ft_strdup(test_map[i]) : NULL;
//         if (test_map[i] && !game.map.map[i])
//             return (1);
//     }

//     game.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
//     game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
//     if (calculate_map_dimensions(&game))
//     {
//         ft_putstr_fd("Error: Invalid map dimensions\n", 2);
//         return (1);
//     }
//     set_player_pos(&game);
//     load_textures(&game);
//     mlx_image_to_window(game.mlx, game.img, 0, 0);
//     mlx_loop_hook(game.mlx, ft_gaming, &game);
//     mlx_loop(game.mlx);
//     // Note: Add cleanup (free game.map.map) here if needed
//     return (0);
// }
