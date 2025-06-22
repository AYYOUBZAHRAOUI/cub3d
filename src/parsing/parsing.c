/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzahrao <ayzahrao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:17:02 by ayzahrao          #+#    #+#             */
/*   Updated: 2025/06/22 05:27:45 by ayzahrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * @brief check if the file exists and if it is a valid texture file
 * @param map the map to check
 * @return 1 if the file exists and is a valid texture file,
 *  0 if the file does not exist or is not a valid texture file
 * @note this function will print an error message 
 * if the file does not exist or is not a valid texture file
*/
int	check_exist_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error:");
		return (0);
	}
	close(fd);
	return (1);
}

int	check_files(t_map *map)
{
	if (!check_exist_file(map->no)
		|| !check_exist_file(map->so)
		|| !check_exist_file(map->we)
		|| !check_exist_file(map->ea))
	{
		perror("Error:");
		return (0);
	}
	return (1);
}

/*
 * @brief the main function to parse the file .cub and fill the map structure
 * ! the demotions of the map are not checked in this function
 * @param file the file to parse
 * @param map the map to fill
 * @return 1 if the map is valid, 0 if the map is invalid
 * @note this function will print an error message if the file is invalid
*/
int	parse_map(char *file, t_map *map)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd > -1)
	{
		if (parse_texture_and_color(fd, map)
			&& check_files(map)
			&& parse_map_lines(fd, map)
			&& check_map(map->map))
		{
			calculate_map_dimensions(map);
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

/*
 * @brief parse the map lines of texture and color
 * @param fd the file descriptor of the map file
 * @param map the map to fill
 * @return 1 if the map is valid, 0 if the map is invalid
 * @note this function prints an error message if the map is invalid
 
*/
int	parse_texture_and_color(int fd, t_map *map)
{
	char	*line;
	int		found_textures;
	char	*trim_line;

	found_textures = 0;
	line = skip_empty_lines(fd);
	while (found_textures < 6 && line != NULL)
	{
		trim_line = ft_strtrim(line, " \t\n");
		if (parse_one_line(trim_line, map))
			found_textures++;
		else
			return (free(line), free(trim_line), 0);
		free(line);
		free(trim_line);
		if (found_textures < 6)
			line = skip_empty_lines(fd);
	}
	if (found_textures != 6)
	{
		ft_putstr_fd("Error: Missing textures or colors\n", 2);
		return (0);
	}
	return (parse_rgb_colors(map));
}

/*
 * @brief parse one line and check if it is a valid texture identifier
 * @param line the line to parse
 * @param map the map to fill
 * @return 1 if the line is valid, 0 if the line is invalid
 * @note this function prints an error message if the line is invalid
*/
int	parse_one_line(char *line, t_map *map)
{
	int	parse_result;

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
 * @brief parse the line and check if it is a valid texture identifier
 * @param line the line to parse
 * @param identifier the identifier to check (NO, SO, WE, EA, F, C)
 * @param texture the texture to fill 
 *		*(map->no, map->so, map->we, map->ea, map->floor_color, map->ceiling_color)
 * @return 1 if the line is valid, 0 if the line is invalid
 * @note this function will also check if the texture is already set
 * 	* and will return -1 if it is already set
 * @note this function prints an error message if the texture is already set !
*/
int	parse_id_line(char *line, char *identifier, char **texture)
{
	int		id_len;
	char	*path;
	char	*newline;

	id_len = ft_strlen(identifier);
	if (ft_strncmp(line, identifier, id_len) == 0)
	{
		if (line[id_len] == ' ' || line[id_len] == '\t')
		{
			if (*texture)
				return (ft_putstr_fd("Error: Duplicate texture\n", 2), -1);
			path = line + id_len;
			while (*path == ' ' || *path == '\t')
				path++;
			newline = ft_strchr(path, '\n');
			if (newline)
				*newline = '\0';
			*texture = ft_strdup(path);
			if (!*texture)
				return (perror("Error Memory allocation failed"), 0);
			return (1);
		}
	}
	return (0);
}

/*
 * @brief calculate the dimensions of the map
 * @param map the map to calculate the dimensions of
*/
void	calculate_map_dimensions(t_map *map)
{
	int	i;
	int	width;

	i = 0;
	while (map->map[i])
		i++;
	map->height = i;
	width = ft_strlen(map->map[0]);
	map->width = width;
}
