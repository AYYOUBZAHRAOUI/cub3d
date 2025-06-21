/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybekach <ybekach@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:33:59 by ayzahrao          #+#    #+#             */
/*   Updated: 2025/06/21 21:23:06 by ybekach          ###   ########.fr       */
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

/*
----------- you need to create a basic trunctur but not to day ----------
*/
typedef struct s_player
{
	double	x;
	double	y;
	double	fov;
	double	angle;
}				t_player;

typedef struct rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;

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
}    t_map;

typedef struct s_ray
{
    double    dist;
    double    wall_hit_x;
    double    wall_hit_y;
    int        hit_vertical;
    int        tex_dir;
}    t_ray;

typedef struct s_texture
{
    mlx_texture_t	*tex;
    mlx_image_t        *img;
}    t_texture;

typedef struct s_game
{
    mlx_t        *mlx;
    mlx_image_t    *img;
    t_player    player;
    t_texture    textures[4]; // 0: for west example 1: east 2; south 3: north
    t_map        map;
}    t_game;

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

/* ---------------------------------------------- */
/* ----------- RAYS CASTING FUNCTION ------------ */
/* ---------------------------------------------- */
void		calculate_map_dimensions(t_game *game);
int    	is_wall_at(t_game *game, double x, double y);
double  normalize_angle(double angle);
t_ray   cast_ray(t_game *game, double angle);
void    draw_background(t_game *game);
void    draw_3d_walls(t_game *game);
void    move_player_ws(t_game *game, double step, int dir);
void    move_player_ad(t_game *game, double step, int dir);
void    handle_input(t_game *game);
void    ft_gaming(void *param);
void    set_player_pos(t_game *game);
void    load_textures(t_game *game);

#endif
