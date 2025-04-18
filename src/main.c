#include "../include/cub3d.h"


int main(int ac, char **av)
{
    char *x;
    int fd;
    t_map m;

    
    check_argument(ac, av);
    // open to read this file X.cub
    fd = open(av[1], O_RDONLY);
    printf("hello im fd = %i\n", fd);
    if (fd < 0)
    {
        perror("Error");
        return(1);
    }
    parsing(m, fd);

    return (0);
}