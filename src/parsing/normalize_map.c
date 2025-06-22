/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzahrao <ayzahrao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 01:24:35 by ayzahrao          #+#    #+#             */
/*   Updated: 2025/06/22 05:23:37 by ayzahrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * @breif maxlength of the map
	* @param map the map to check is a double pointer of char
	* @return the length of the longest line
*/
int	get_max_length(char **map)
{
	int	max_length;
	int	i;
	int	length;

	max_length = 0;
	i = 0;
	while (map[i])
	{
		length = ft_strlen(map[i]);
		if (length > max_length)
			max_length = length;
		i++;
	}
	return (max_length);
}

/*
 * @brief count the number of lines in the map
	* @param map the map to check is a double pointer of char
	* @return the number of lines in the map
	* Check for empty lines at the end of the map
*/
int	count_lines(char **map)
{
	int		count;
	char	*trim_line;

	count = 0;
	while (map[count])
		count++;
	while (count > 0)
	{
		trim_line = ft_strtrim(map[count - 1], " \t\n");
		if (*trim_line == '\0')
		{
			free(trim_line);
			count--;
		}
		else
		{
			free(trim_line);
			break ;
		}
	}
	return (count);
}

/*
 * @brief fill the line with spaces
	* @param line the line to fill
	* @param max_length the length of the line
	* @return void
*/
void	fill_line_by_spaces(char *line, int max_length)
{
	int	i;

	i = 0;
	while (i < max_length)
	{
		line[i] = ' ';
		i++;
	}
	line[i] = '\0';
}

/*
 * @brief normalize the map
	* @param map the map to normalize is a double pointer of char
	* @return the normalized map
	* @note this function will normalize the map by filling 
	the empty spaces with ' '
	* and make sure that all lines are the same length
	* @warning is possible to have lines with different length 
	there is have two '\0'
	* @warning this function don't protect against memory leaks
	* @note this function will also free the old map
*/
char	**normalize_map(char **map)
{
	int		max_length;
	char	**normalized;
	int		i;
	int		num_lines;

	max_length = get_max_length(map);
	num_lines = count_lines(map);
	normalized = malloc((num_lines + 1) * sizeof(char *));
	if (normalized == NULL)
		return (perror("Error"), NULL);
	i = -1;
	while (++i < num_lines)
	{
		normalized[i] = malloc((max_length + 1) * sizeof(char));
		fill_line_by_spaces(normalized[i], max_length);
		ft_memcpy(normalized[i], map[i], ft_strlen(map[i]));
	}
	normalized[num_lines] = NULL;
	return (free_str_array(map), normalized);
}
