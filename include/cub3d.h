#ifndef CUB3D_H
#define CUB3D_H

#include <map>
#include <math.h>
#include <sys/types.h> // i need to understand this library
#include <sys/stat.h> // i need to understand this library
#include <sys/time.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../libft/include/libft.h"

/*
----------- you need to create a basic trunctur but not to day ----------
*/
typedef struct rgb
{
    unsigned int red;
    unsigned int grean;
    unsigned int blue;
} t_rgb;

typedef struct  map
{
    char *so;
    char *no;
    char *we;
    char *ea;
    t_rgb f;
    t_rgb c;
    char **map;
} t_map;

/*
---------- functions prototypes ------------
*/
void check_argument(int ac, char **av);
void parsing(t_map *m, int fd); 






#endif