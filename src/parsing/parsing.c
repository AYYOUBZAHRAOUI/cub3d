/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayyoubz <ayyoubz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:17:02 by ayzahrao          #+#    #+#             */
/*   Updated: 2025/06/05 18:50:47 by ayyoubz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_exist_file(t_map *map){
	int fd1 = open(map->no, O_RDONLY);
	int fd2 = open(map->so, O_RDONLY);
	int fd3 = open(map->ea, O_RDONLY);
	int fd4 = open(map->we, O_RDONLY);

	// printf("ea: %d '%s'\n", fd4,map->ea);
	if(fd1 < 0 || fd2 < 0 || fd3 < 0 || fd4 < 0){
		perror("Error ");
		close(fd1);
		close(fd2);
		close(fd3);
		close(fd4);
		return 0;
	}
	else{
		close(fd1);
		close(fd2);
		close(fd3);
		close(fd4);
		return 1;
	}
}

/*
 * @brief the main function to parse the map
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
			&& check_exist_file(map)
			&& parse_map_lines(fd, map)
			&& print_map(map)
			&& printf("Map parsed successfully\n")
			&& check_map(map->map)
			&& printf("Map is valid\n"))
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
 * @note this function prints an error message if the line is invalid
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
