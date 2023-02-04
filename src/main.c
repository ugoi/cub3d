/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:10:52 by stefan            #+#    #+#             */
/*   Updated: 2023/02/04 21:53:23 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_module.h"
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

int player_constructor(t_map *map, t_player *player)
{
	int			i;
	int			j;

	i = 0;
	while (map->raw_map[i])
	{
		j = 0;
		while (map->raw_map[i][j])
		{
			if (map->raw_map[i][j] == 'N' || map->raw_map[i][j] == 'S' || map->raw_map[i][j] == 'W' || map->raw_map[i][j] == 'E')
			{
				player->pos.y = i;
				player->pos.x = j;
				if (map->raw_map[i][j] == 'N')
					player->radians = 3.0 / 2.0 * M_PI;
				else if (map->raw_map[i][j] == 'S')
					player->radians = M_PI / 2.0;
				else if (map->raw_map[i][j] == 'W')
					player->radians = M_PI;
				else if (map->raw_map[i][j] == 'E')
					player->radians = 0;
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

// void map_constructor(t_map *map)
// {
// 	char		*map_file;
	
// 	map_file = "./maps/map1.txt";
// 	map->raw_map = init_raw_map(map_file);
// 	map->raw_map_dimensions = get_map_dimesnions(map->raw_map);
// 	map->minimap_dimensions = (t_int_vector){WIDTH / 4, WIDTH / 4};
// 	map->minimap_scaling_factor = get_fscaling_factor(map->raw_map_dimensions, map->minimap_dimensions);
// }

int	main(void)
{
	t_map		map;
	t_player	player;

	map_constructor(&map);
	player_constructor(&map, &player);
	init_window(&map, &player);
}
