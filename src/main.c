#include "cub3d.h"

int	main(int ac, char **av)
{
	t_map	map;
	if (check_args(ac, av) == 0)
		return (1);
	int_map(&map);
	if (!(parse_map(av[1], &map)))
		return (1);
	print_map(&map);
	return (0);
}

int int_map(t_map *map)
{
	map->so = NULL;
	map->no = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->floor_color = NULL;
	map->ceiling_color = NULL;
	map->f = NULL;
	map->c = NULL;
	map->map = NULL;
	return (1);
}