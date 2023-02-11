/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:10:52 by stefan            #+#    #+#             */
/*   Updated: 2023/02/11 19:07:59 by sdukic           ###   ########.fr       */
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

// int main(int argc, char *argv[])
// {
// 	int	valid_file;
// 	int	error;
// 	t_map_parsing map;

// 	if (argc != 2)
// 	{
// 		printf("Error\nUsage sample: ./cub3d \"./maps/map01.cub\"\n");
// 		return (EXIT_FAILURE);
// 	}
// 	valid_file = is_file_valid(argv);
// 	if (valid_file != 0)
// 	{
// 		return (EXIT_FAILURE);
// 	}
// 	error = parse_map(argv[1], &map);
// 	if (error != 0)
// 	{
// 		printf("Error:%d:*\n", error);
// 		return (EXIT_FAILURE);
// 	}
// 	printf("%s\n", map.textures.east_path);
// 	printf("%s\n", map.textures.north_path);
// 	printf("%s\n", map.textures.west_path);
// 	printf("%s\n", map.textures.south_path);
// 	// Do a check for TEXTURE path if it is valid  !+++===========================IMPORTANT=========================+++++!
// 	// is_wall_texture_valid(&map);
// 	printf("%d, %d, %d\n", map.textures.ceiling1, map.textures.ceiling2, map.textures.ceiling3);
// 	printf("%d, %d, %d\n", map.textures.floor1, map.textures.floor2, map.textures.floor3);
// 	while (*map.cub3d_map)
// 	{
// 		printf("%s", *map.cub3d_map);
// 		map.cub3d_map++;
// 	}
// 	// system("leaks a.out");
// 	return (EXIT_SUCCESS);
// }
