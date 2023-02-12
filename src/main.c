/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:10:52 by stefan            #+#    #+#             */
/*   Updated: 2023/02/12 17:47:23 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics_module.h"
#include "./include/colors.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <math.h>
#include "./include/map.h"
#include "./parser/parser.h"
#include "../lib/gnl/get_next_line.h"

int	main(int argc, char *argv[])
{
	t_map			map;
	t_player		player;
	t_map_parsing	map_parsing;
	int				error;

	(void)map_parsing;
	if (argc != 2)
	{
		printf("Error\nUsage sample: ./cub3d \"./maps/map01.cub\"\n");
		return (EXIT_FAILURE);
	}
	if (is_file_valid(argv) != 0)
	{
		return (EXIT_FAILURE);
	}
	error = parse_map(argv[1], &map_parsing);
	if (error != 0)
	{
		printf("Error:%d:*\n", error);
		return (EXIT_FAILURE);
	}
	map_constructor(&map, &map_parsing);
	player_constructor(map.raw_map, &player);
	init_window(&map, &player);
}
