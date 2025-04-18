#include "../include/cub3d.h"

/*
* breaf : check the requirement of argument
* if sumting invalide print an error message and exit
* arg ac : numeber of arguments (argc)
* arg av : array of arguement string (argv)
*/
void check_argument(int ac, char **av)
{
    if (ac != 2)
    {
        perror("Error: invalide argument");
        exit(1);
    }
    if (ft_strlen(av[1]) >= 5
        && !ft_strncmp(av[1]+(ft_strlen(av[1]) - 4), ".cub", 4)
        && *(av[1] + (ft_strlen(av[1]) - 5)) != '/')
        ;
    else
    {
        perror("Error: invalide argument");
        exit(1); // i don't  now wat is the number i need exite with 
    }
}

/*
i need a function to parse
what this function do 
1. parse the first 4 lines so, no, we, ea
2. parse the two lines f and c;
3. parse the map of n line >= 3 len > 3
*/
void parsing(t_map *m, int fd)
{
    
}