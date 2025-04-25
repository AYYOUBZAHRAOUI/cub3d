#include "cub3d.h"

int check_args(int ac, char **av)
{
	if (ac == 2)
	{
		if ( ft_strlen(av[1]) > 5
			&& ft_strncmp(ft_strrchr(av[1], '.'), ".cub", 4) == 0)
			return (1);
		else
		{
			perror("Error\nInvalid argument\n");
			return (0);
		}
	}
	else
	{
		perror("Error\nInvalid number of arguments\n");
		return (0);
	}
}

int parse_map(char *file, t_map *map)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (fd > -1)
    {
        if (parse_texture_and_color(fd, map))
        {
            close(fd);
            return (1);
        }
        close(fd);
        return (0);
    }
    else
    {
        perror("Error");
        return (0);
    }
}


int parse_texture_and_color(int fd, t_map *map)
{
    char *line;
    int found_textures;
    char *trim_line;

    found_textures = 0;
    line = ft_get_next_line(fd);
    while (found_textures < 6 && line != NULL)
    {
        trim_line = ft_strtrim(line, " \t");
        if (*trim_line == '\n' || *trim_line == '\0')
        {
            free(line);
            line = ft_get_next_line(fd);
            continue;
        }
        if (parse_one_line(trim_line, map))
            found_textures++;
        else
            return (free(line), 0);
        free(line);
        line = ft_get_next_line(fd);
    }
    if (found_textures != 6)
    {
        ft_putstr_fd("Error: Missing textures or colors\n", 2);
        return (0);
    }
    if (!parse_rgb_colors(map))
        return (0);
    return (1);
}

int parse_one_line(char *line, t_map *map)
{
    int parse_result;

    parse_result = parse_id_line(line, "NO", &map->no);
    if (parse_result != 0)
        return (parse_result == 1);
    parse_result = parse_id_line(line, "SO", &map->so);
    if (parse_result != 0)
        return (parse_result == 1);
    parse_result = parse_id_line(line, "WE", &map->we);
    if (parse_result != 0)
        return (parse_result == 1);
    parse_result = parse_id_line(line, "EA", &map->ea);
    if (parse_result != 0)
        return (parse_result == 1);
    parse_result = parse_id_line(line, "F", &map->floor_color);
    if (parse_result != 0)
        return (parse_result == 1);
    parse_result = parse_id_line(line, "C", &map->ceiling_color);
    if (parse_result != 0)
        return (parse_result == 1);
    perror("Error: Invalid texture identifier");
    return (0);
}



/*
 * Check if the line starts with the identifier
 * Check if the character after the identifier is a space or tab
 * Check for duplicate
 * Skip spaces after identifier
 * Remove trailing newline if present
 * Duplicate the path
 * return 0 to try the next one if Not this identifier
*/
int parse_id_line(char *line, char *identifier, char **texture)
{
    int id_len;
    char *path;

    id_len = ft_strlen(identifier);
    if (ft_strncmp(line, identifier, id_len) == 0)
    {
        if (line[id_len] == ' ' || line[id_len] == '\t')
        {
            if (*texture)
            {
                ft_putstr_fd("Error: Duplicate texture\n", 2);
                return (-1);
            }
            path = line + id_len;
            while (*path == ' ' || *path == '\t')
                path++;
            char *newline = ft_strchr(path, '\n');
            if (newline)
                *newline = '\0';
            *texture = ft_strdup(path);
            if (!*texture)
            {
                perror("Error Memory allocation failed");
                return (0);
            }
            return (1);
        }
    }
    return (0);
}
