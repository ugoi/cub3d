/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:10:52 by stefan            #+#    #+#             */
/*   Updated: 2023/02/01 15:49:03 by stefan           ###   ########.fr       */
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

char *get_next_line(int fd) 
{
    char *string = malloc(10000), *copy = string;
    while (read(fd, copy, 1) > 0 && *copy++ != '\n');
    return (copy > string) ? (*copy = 0, string) : (free(string), NULL);
}

char	**init_raw_map(char *map_file)
{
	char	**map;
	int		fd;
	int		i;
	int		j;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening map file %s\n", map_file);
		exit(1);
	}
	i = 0;
	while (get_next_line(fd))
	{
		i++;
	}
	close(fd);
	printf("i = %d\n", i);
	fd = open(map_file, O_RDONLY);
	map = malloc(sizeof(char *) * (i + 1));
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		j = 0;
		map[i] = malloc(sizeof(char) * 10);
		while (line[j] && line[j] != '\n')
		{
			map[i][j] = line[j];
			j++;
		}
		map[i][j] = 0;
		i++;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

int init_player(t_map *map, t_player *player)
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
					player->dir = (t_float_vector){0, 1};
				else if (map->raw_map[i][j] == 'S')
					player->dir = (t_float_vector){0, -1};
				else if (map->raw_map[i][j] == 'W')
					player->dir = (t_float_vector){-1, 0};
				else if (map->raw_map[i][j] == 'E')
					player->dir = (t_float_vector){1, 0};
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

#include <math.h>
#include <stdlib.h>


int	main(void)
{
	t_map		map;
	char		*map_file;
	t_player	player;
	
	map_file = "./maps/map1.txt";
	map.raw_map = init_raw_map(map_file);
	printf("map\n");
	init_player(&map, &player);
	init_window(&map, &player);
}