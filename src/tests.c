/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzahrao <ayzahrao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:51:29 by ayzahrao          #+#    #+#             */
/*   Updated: 2025/05/08 14:52:41 by ayzahrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * this function prints the structure map
*/
int	print_map(t_map *map)
{
	char	**x;

	printf("North texture: %s\n", map->no);
	printf("South texture: %s\n", map->so);
	printf("West texture: %s\n", map->we);
	printf("East texture: %s\n", map->ea);
	printf("floor color: %s\n", map->floor_color);
	printf("Ceiling color: %s\n", map->ceiling_color);
	printf("Ceiling color R: %d; G: %d; B: %d;\n",
		map->c->red, map->c->grean, map->c->blue);
	printf("floor color R: %d; G: %d; B: %d;\n",
		map->f->red, map->f->grean, map->f->blue);
	x = map->map;
	if (x == NULL)
	{
		printf("map is NULL\n");
	}
	while (x && *x)
	{
		printf("%s\n", *x);
		x++;
	}
	return (1);
}
