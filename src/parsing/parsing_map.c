/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzahrao <ayzahrao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:32:03 by ayzahrao          #+#    #+#             */
/*   Updated: 2025/05/08 15:58:44 by ayzahrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * @brief check if the line is empty
 * @param line the line to check
 * @return 1 if the line is not empty, 0 if the line is empty
 * @note this function prints an error message if the line is empty
 * @noe this function used in parse_map_lines to 
 * check if there is empty lines inside the map
*/
int	check_empty_lines(char *line)
{
	char	*trim_line;

	trim_line = ft_strtrim(line, " \t\n");
	if (trim_line[0] == '\0')
	{
		free(trim_line);
		ft_putstr_fd("Error: Map have a empty line\n", 2);
		return (0);
	}
	free(trim_line);
	return (1);
}

/*
 * @brief parse the map lines and check if they are valid
 * @param fd the file descriptor of the map file
 * @param map the map to fill
 * @return 1 if the map is valid, 0 if the map is invalid
 * @note this function prints an error message if the map is invalid
*/
int	parse_map_lines(int fd, t_map *map)
{
	char	*line;
	char	*big_line;
	char	*tmp;

	big_line = NULL;
	line = skip_empty_lines(fd);
	while (line)
	{
		if (check_empty_lines(line) == 0)
			return (free(big_line), free(line), 0);
		tmp = big_line;
		big_line = ft_strjoin(big_line, line);
		if (tmp)
			free(tmp);
		free(line);
		line = ft_get_next_line(fd);
	}
	if (!big_line)
	{
		ft_putstr_fd("Error: Map is empty\n", 2);
		return (0);
	}
	map->map = normalize_map(ft_split(big_line, '\n'));
	return (free(big_line), free(line), 1);
}

/*
 * @brief skip the empty lines in the map
 * @param fd the file descriptor of the map file
 * @return the line that is not empty 
 * or NULL if the end of the file is reached
*/
char	*skip_empty_lines(int fd)
{
	char	*line;
	char	*trim_line;

	line = ft_get_next_line(fd);
	while (line)
	{
		trim_line = ft_strtrim(line, " \t\n");
		if (*trim_line == '\0')
		{
			free(trim_line);
			free(line);
			line = ft_get_next_line(fd);
			continue ;
		}
		free(trim_line);
		break ;
	}
	return (line);
}
