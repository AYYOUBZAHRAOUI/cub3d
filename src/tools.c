/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzahrao <ayzahrao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:13:01 by ayzahrao          #+#    #+#             */
/*   Updated: 2025/05/08 15:46:12 by ayzahrao         ###   ########.fr       */
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
