#ifndef CUB3D_H
#define CUB3D_H

#include <math.h>
#include <sys/types.h> // i need to understand this library
#include <sys/stat.h> // i need to understand this library
#include <sys/time.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "libft.h"
#include "MLX42.h"

/*
----------- you need to create a basic trunctur but not to day ----------
*/
typedef struct rgb
{
    int red;
    int grean;
    int blue;
} t_rgb;

typedef struct  map
{
    char *so;
    char *no;
    char *we;
    char *ea;
    char *floor_color;
    char *ceiling_color;
    t_rgb *f;
    t_rgb *c;
    char **map;
} t_map;

/* ----------- PARSING FUNCTION ------------ */
int check_args(int ac, char **av);
int parse_map(char *file, t_map *map);
int parse_texture_and_color(int fd, t_map *map);
void free_split(char **split);
int parse_color(char *color_str, t_rgb **rgb);
int parse_rgb_colors(t_map *map);
int parse_one_line(char *line, t_map *map);
int parse_id_line(char *line, char *identifier, char **texture);
int check_color(char *color_str, int *color);
/* ----------- TEST FUNCTION -------------- */
void print_map(t_map *map);

/* ----------- UTILS FUNCTION ------------ */
int int_map(t_map *map);


#endif