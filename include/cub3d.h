/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzahrao <ayzahrao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:33:59 by ayzahrao          #+#    #+#             */
/*   Updated: 2025/06/22 05:20:51 by ayzahrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <sys/types.h> // i need to understand this library
# include <sys/stat.h> // i need to understand this library
# include <sys/time.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# include "libft.h"
# include "MLX42.h"

# define WIDTH 800
# define HEIGHT 600
# define TILE_SIZE 64
# define NUM_RAYS WIDTH

/* -------------------------------------------------------------- */
/* ------------------------ STRUCTURES -------------------------- */
/* -------------------------------------------------------------- */

/*
 * @brief Player structure to hold player position, field of view, and angle
 * 
 * @param x : Player's x-coordinate
 * @param y : Player's y-coordinate
 * @param fov: Field of view in radians
 * @param angle: Direction the player is facing in radians
*/
typedef struct s_player
{
	double	x;
	double	y;
	double	fov;
	double	angle;
}				t_player;

/*
 * @brief RGB structure to hold color values
 *
 * @param red: Red color component (0-255)
 * @param green: Green color component (0-255)
 * @param blue: Blue color component (0-255)
*/
typedef struct rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;

/*
 * @brief Map structure to hold the map data, dimensions, textures, and colors
 *
 * @param map: 2D array of strings representing the map
 * @param height: Height of the map (number of rows)
 * @param width: Width of the map (number of columns)
 * @param so: Path to south texture
 * @param no: Path to north texture
 * @param we: Path to west texture
 * @param ea: Path to east texture
 * @param floor_color: String representation of the floor color
 * @param ceiling_color: String representation of the ceiling color
 * @param f: RGB structure for floor color
 * @param c: RGB structure for ceiling color
*/
typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
	char	*so;
	char	*no;
	char	*we;
	char	*ea;
	char	*floor_color;
	char	*ceiling_color;
	t_rgb	*f;
	t_rgb	*c;
}	t_map;

/*
 * @brief Ray structure to hold ray casting data
 *
 * @param dist: Distance to the wall hit by the ray
 * @param wall_hit_x: X-coordinate of the wall hit
 * @param wall_hit_y: Y-coordinate of the wall hit
 * @param hit_vertical: Flag indicating if the ray hit a vertical wall
 * @param tex_dir: Texture direction (0: west, 1: east, 2: south, 3: north)
*/
typedef struct s_ray
{
	double	dist;
	double	wall_hit_x;
	double	wall_hit_y;
	int		hit_vertical;
	int		tex_dir;
}	t_ray;

/*
 * @brief Texture structure to hold texture and image data
 *
 * @param tex: Pointer to the texture data
 * @param img: Pointer to the image data
 * This structure is used to manage textures for different walls in the game.
*/
typedef struct s_texture
{
	mlx_texture_t	*tex;
	mlx_image_t		*img;
}	t_texture;

/*
 * @brief Game structure to hold the game state, player, textures, and map
 *
 * @param mlx: Pointer to the MLX instance
 * @param img: Pointer to the image being rendered
 * @param player: Player structure containing player data
 * @param textures: Array of textures for different walls
     * textures[0]: North wall texture
	 * textures[1]: South wall texture
	 * textures[2]: West wall texture
	 * textures[3]: East wall texture
 * @param map: Map structure containing map data and textures
*/
typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	player;
	t_texture	textures[4];
	t_map		map;
}	t_game;

/* ----------------------------------------- */
/* ----------- PARSING FUNCTION ------------ */
/* ----------------------------------------- */

/* ------------ CHECK FUNCTIONS ------------ */
int		check_args(int ac, char **av);
int		check_map(char **map);
int		check_map_characters(char **map);
int		check_map_walls_1(char **map);
int		check_map_walls_2(char **map);
int		check_color(char *color_str, int *color);

/* ------------- PARSE FUNCTIONS ------------- */
int		parse_map(char *file, t_map *map);
int		parse_texture_and_color(int fd, t_map *map);
int		parse_one_line(char *line, t_map *map);
int		parse_color(char *color_str, t_rgb **rgb);
int		parse_rgb_colors(t_map *map);
int		parse_id_line(char *line, char *identifier, char **texture);
int		parse_map_lines(int fd, t_map *map);

/* ----------- CHECK MAP FUNCTIONS ----------- */
char	**normalize_map(char **map);
char	*skip_empty_lines(int fd);
void	free_str_array(char **split);

/* ----------- MAP STRUCT TOOLS ------------ */
void	free_map(t_map *map);
void	int_map(t_map *map);

/* ----------- TEST FUNCTION -------------- */
int		print_map(t_map *map);

/* ----------- UTILS FUNCTION ------------ */
void	calculate_map_dimensions(t_map *map);

/* ---------------------------------------------- */
/* ----------- RAYS CASTING FUNCTION ------------ */
/* ---------------------------------------------- */
int		is_wall_at(t_game *game, double x, double y);
double	normalize_angle(double angle);
t_ray	cast_ray(t_game *game, double angle);
void	draw_background(t_game *game);
void	draw_3d_walls(t_game *game);
void	move_player_ws(t_game *game, double step, int dir);
void	move_player_ad(t_game *game, double step, int dir);
void	handle_input(t_game *game);
void	ft_gaming(void *param);
void	set_player_pos(t_game *game);
int		load_textures(t_game *game);

#endif
