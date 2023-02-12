/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:24:21 by sdukic            #+#    #+#             */
/*   Updated: 2023/02/12 18:52:55 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/map.h"
#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "MLX42.h"
#include "./include/player.h"
#include "./include/colors.h"
#include "./include/my_math.h"
#include "../lib/libft/libft.h"
#include "./include/my_error.h"

int	draw_player(mlx_image_t *map_img, t_player *player, t_map *map)
{
	float				scaling_factor;
	int					player_size;
	int					top_left_x;
	int					top_left_y;

	scaling_factor = map->minimap_scaling_factor;
	player_size = scaling_factor / 4;
	top_left_x = player->pos.x * scaling_factor;
	while (top_left_x < player->pos.x * scaling_factor + player_size)
	{
		top_left_y = player->pos.y * scaling_factor;
		while (top_left_y < player->pos.y * scaling_factor + player_size)
		{
			mlx_put_pixel(map_img, top_left_x, top_left_y,
				get_rgba(0, 255, 0, 255));
			top_left_y++;
		}
		top_left_x++;
	}
	return (0);
}

int	draw_map(mlx_image_t *map_img, t_map *map, t_player *player)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	y = 0;
	while (map->mini_map[y])
	{
		while (map->mini_map[y][x])
		{
			if (map->mini_map[y][x] == '1')
				mlx_put_pixel(map_img, x, y, get_rgba(255, 255, 255, 255));
			else
				mlx_put_pixel(map_img, x, y, get_rgba(0, 0, 0, 255));
			x++;
		}
		x = 0;
		y++;
	}
	draw_player(map_img, player, map);
	return (0);
}
