/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzahrao <ayzahrao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:13:01 by ayzahrao          #+#    #+#             */
/*   Updated: 2025/06/26 19:11:43 by ayzahrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * @brief free the map structure
 * @param map the map to free
 * @return void
 * @note this func check every pointer in the map structure and free it
*/
void	free_map(t_map *map)
{
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->ea)
		free(map->ea);
	if (map->floor_color)
		free(map->floor_color);
	if (map->ceiling_color)
		free(map->ceiling_color);
	if (map->f)
		free(map->f);
	if (map->c)
		free(map->c);
	if (map->map)
		free_str_array(map->map);
}

/*
 * @brief initialize the map structure
*/
void	int_map(t_map *map)
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
}

/*
 * @brief free every string in the array and then free the array
 * @param split the string array to free
 * @return void
*/
void	free_str_array(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

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
