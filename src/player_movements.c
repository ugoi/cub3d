/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:10:52 by stefan            #+#    #+#             */
/*   Updated: 2023/02/13 00:34:58 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics_module.h"
#include "./include/colors.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include "MLX42.h"
#include <math.h>
#include "./include/my_math.h"
#include "./include/map.h"
#include "./include/ray.h"
#include "./include/my_error.h"

void	move_player(float dist, float dir, t_player *player, t_map map)
{
	float			collision_dist;
	t_float_vector	collision_point;

	collision_dist = 0.11;
	collision_point.x = player->pos.x
		+ dist * collision_dist * cos(player->radians + dir);
	collision_point.y = player->pos.y
		+ dist * collision_dist * sin(player->radians + dir);
	if (map.raw_map[(int)player->pos.y]
		[(int)collision_point.x] != '1')
		player->pos.x += dist * 0.1 * cos(player->radians + dir);
	if (map.raw_map[(int)collision_point.y]
		[(int)player->pos.x] != '1')
		player->pos.y += dist * 0.1 * sin(player->radians + dir);
}

void	rotate_player(float angle, t_player *player)
{
	player->radians = add_radians(player->radians, angle);
}
