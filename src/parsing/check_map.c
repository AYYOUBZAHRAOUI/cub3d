/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzahrao <ayzahrao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:31:45 by ayzahrao          #+#    #+#             */
/*   Updated: 2025/05/29 22:37:51 by ayzahrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * @brief check if the arguments are valid
 * @param ac the number of arguments
 * @param av the arguments	
 * @return 1 if the arguments are valid, 0 if the arguments are invalid
 * @note this function handle error messages
*/
int	check_args(int ac, char **av)
{
	if (ac == 2)
	{
		if (ft_strlen(av[1]) > 5
			&& ft_strncmp(ft_strrchr(av[1], '.'), ".cub", 4) == 0)
			return (1);
		else
		{
			ft_putstr_fd("Error: Invalid argument\n", 2);
			return (0);
		}
	}
	else
	{
		ft_putstr_fd("Error: Invalid number of arguments\n", 2);
		return (0);
	}
}

/*
 * @brief check if the map is valid
	* @param map the map to check is a double pointer of char 
	* @return 1 if the map is valid, 0 if the map is invalid
	* @note this function handle error messages
*/
int	check_map(char **map)
{
	if (check_map_characters(map) == 0)
	{
		ft_putstr_fd("Error: Map have invalid characters or miss one or more\n", 2);
		return (0);
	}
	printf("debug: 1 \n");
	if (check_map_walls_1(map) == 0)
	{
		ft_putstr_fd("Error: Map is not surrounded by walls\n", 2);
		return (0);
	}
	return (1);
}

/*
 * @brief check if the map have just the characters '1', '0', ' ', 
 * and one of 'N', 'S', 'E', 'W'
	* @param map the map to check is a double pointer of char
	* @return 1 if the map is valid, 0 if the map is invalid
*/
int	check_map_characters(char **map)
{
	int	i;
	int	j;
	int	checked;
	int	zero;

	checked = 0;
	zero = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' ')
			{
				if ((map[i][j] == 'N' || map[i][j] == 'S' 
				|| map[i][j] == 'E' || map[i][j] == 'W') && !checked)
					checked = 1;
				else
					return (0);
			}
			if (map[i][j] == '0' && zero == 0)
				zero = 1;
		}
	}
	return (checked && zero);
}

/*
 * @brief check if the map is surrounded by walls
	* @param map the map to check, is a double pointer of char
	* @return 1 if map is valid, 0 if the map is invalid
	* @note how this function work
	*   * take every 0 or player char (S N E W) and check is surrounded by 0 or 1
	*   * if is note that meed is surround by space 
	*	* or '\0' of is in the first line of last line or first char in line
*/
int	check_map_walls_1(char **map)
{
	int	i;
	int	j;

	j = 0;
	while (map[j])
	{
		if (j == 0 || map[j + 1] == NULL)
		{
			i = 0;
			while (map[j][i])
			{
				if (map[j][i] != '1' && map[j][i] != ' ')
					return (0);
				i++;
			}
		}
		if (map[j][0] != '1' && map[j][0] != ' ')
			return (0);
		j++;
	}
	printf("debug: 2 \n");
	if (check_map_walls_2(map) == 0)
	{
		printf("debug: 3 \n");
		return (0);
	}
	return (1);
}

/*
 * @brief help function of check_map_walls_1
*/
int	check_map_walls_2(char **map)
{
	int	i;
	int	j;

	i = 1;
	while (map[i + 1])
	{
		j = 1;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != ' ')
			{
				if (!((map[i][j - 1] != ' ' && map[i][j - 1] != '\0')
					&& (map[i - 1][j] != ' ' && map[i - 1][j] != '\0')
					&& (map[i][j + 1] != ' ' && map[i][j + 1] != '\0')
					&& (map[i + 1][j] != ' ' && map[i + 1][j] != '\0')))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
