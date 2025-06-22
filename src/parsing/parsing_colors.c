/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzahrao <ayzahrao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:58:47 by ayzahrao          #+#    #+#             */
/*   Updated: 2025/06/22 05:36:38 by ayzahrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * @brief count the number of commas in the string
 * @param str the string to count the commas in
 * @return the number of commas in the string
 * This function helps to determine if the color string is in the correct format
*/
int	count_ver(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

/*
 * @brief parse the RGB colors from the map structure
 * @param map the map structure containing the floor and ceiling colors
 * @return 1 if the colors are parsed successfully, 0 if there is an error
*/
int	parse_rgb_colors(t_map *map)
{
	if (count_ver(map->floor_color) != 2)
	{
		ft_putstr_fd("Error: Invalid floor color", 2);
		return (0);
	}
	if (count_ver(map->ceiling_color) != 2)
	{
		ft_putstr_fd("Error: Invalid ceiling color", 2);
		return (0);
	}
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
 * @brief parse the color string in the format "R,G,B"
 * @param color_str the color string to parse
 * @param rgb a pointer to a t_rgb structure to fill with the parsed color values
 * @return 1 if the color is parsed successfully, 0 if there is an error
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
		perror("Error:");
		return (0);
	}
	if (check_color(values[0], &((*rgb)->red))
		&& check_color(values[1], &((*rgb)->green))
		&& check_color(values[2], &((*rgb)->blue)))
	{
		free_str_array(values);
		return (1);
	}
	free_str_array(values);
	return (0);
}

/*
 * @brief check if the color string is in the format of numbers only
 * @param str the color string to check
 * @return 1 if the string is in the format of numbers only, 0 otherwise
*/
int	is_color_format(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

/*
 * @brief sum check and parse the color value from a string
 * @param color_str the color string to check
 * @param color a pointer to an integer to fill with the parsed color value
 * @return 1 if the color value is valid, 0 otherwise
 * This function trims the input string and checks if it is a valid number
 * in the range of 0 to 255.
*/
int	check_color(char *color_str, int *color)
{
	char	*r_trim;
	int		color_value;

	r_trim = ft_strtrim(color_str, " \t");
	if (is_color_format(r_trim))
		return (free(r_trim), 0);
	color_value = ft_atoi(r_trim);
	free(r_trim);
	if (!(0 <= color_value && color_value <= 255))
		return (0);
	*color = color_value;
	return (1);
}
