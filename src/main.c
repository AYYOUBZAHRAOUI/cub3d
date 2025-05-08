/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzahrao <ayzahrao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:51:13 by ayzahrao          #+#    #+#             */
/*   Updated: 2025/05/08 14:51:14 by ayzahrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	i need a function to check leak memory
*/
void	check_leak(void)
{
	system("leaks -q cub3D");
}

int	main(int ac, char **av)
{
	t_map	map;

	atexit(check_leak);
	if (check_args(ac, av) == 0)
		return (1);
	int_map(&map);
	if (!(parse_map(av[1], &map)))
		return (free_map(&map), 1);
	print_map(&map);
	exit(0);
	return (0);
}
