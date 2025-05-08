/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzahrao <ayzahrao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:58:47 by ayzahrao          #+#    #+#             */
/*   Updated: 2025/05/08 16:14:12 by ayzahrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * @brief parse the colors of the map
 * @param map the map to fill
 * @return 1 if the colors is valid, 0 if the colors is invalid
 * @note this function prints an error message if the colors is invalid
*/
int	parse_rgb_colors(t_map *map)
{
	if (!parse_color(map->floor_color, &map->f))
	{
		ft_putstr_fd("Error: Invalid floor color", 2);
		return (0);
	}
	if (!parse_color(map->ceiling_color, &map->c))
	{
		ft_putstr_fd("Error: Invalid ceiling color", 2);
		return (0);
	}
	return (1);
}

/*
 * @brief parse the color string and check if it is a valid color
 * @param color_str the color string to parse
 * @param rgb the rgb struct to fill
 * @return 1 if the color is valid, 0 if the color is invalid
*/
int	parse_color(char *color_str, t_rgb **rgb)
{
	char	**values;

	values = ft_split(color_str, ',');
	if (!values || !values[0] || !values[1] || !values[2] || values[3])
	{
		if (values)
			free_str_array(values);
		return (0);
	}
	*rgb = malloc(sizeof(t_rgb));
	if (!*rgb)
	{
		free_str_array(values);
		return (0);
	}
	if (check_color(values[0], &((*rgb)->red))
		&& check_color(values[1], &((*rgb)->grean))
		&& check_color(values[2], &((*rgb)->blue)))
	{
		free_str_array(values);
		return (1);
	}
	free_str_array(values);
	free(*rgb);
	return (0);
}

/*
 * @brief convert the color string to int 
 * and check if it is a valid color value
 * @param color_str the color string to convert
 * @param color the color value to fill 
 * (map->f/c->red, map->f/c->green, map->f/c->blue)
 * @return 1 if the color is valid, 0 if the color is invalid
*/
int	check_color(char *color_str, int *color)
{
	char	*r_trim;
	int		color_value;

	r_trim = ft_strtrim(color_str, " \t");
	color_value = ft_atoi(r_trim);
	free(r_trim);
	if (!(0 <= color_value && color_value <= 255))
		return (0);
	*color = color_value;
	return (1);
}
