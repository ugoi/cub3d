/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_movements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:10:52 by stefan            #+#    #+#             */
/*   Updated: 2023/02/12 17:10:31 by sdukic           ###   ########.fr       */
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

void	move_player(t_vars *vars, float dist, float dir)
{
	float			collision_dist;
	t_float_vector	collision_point;

	collision_dist = 0.11;
	collision_point.x = vars->player->pos.x
		+ dist * collision_dist * cos(vars->player->radians + dir);
	collision_point.y = vars->player->pos.y
		+ dist * collision_dist * sin(vars->player->radians + dir);
	if (vars->map->raw_map[(int)vars->player->pos.y]
		[(int)collision_point.x] != '1')
		vars->player->pos.x += dist * 0.1 * cos(vars->player->radians + dir);
	if (vars->map->raw_map[(int)collision_point.y]
		[(int)vars->player->pos.x] != '1')
		vars->player->pos.y += dist * 0.1 * sin(vars->player->radians + dir);
	draw_map(vars->map_img, vars->map, vars->player);
	draw_player(vars->map_img, vars->player, vars->map);
	raycast3d(vars);
}

void	rotate_player(t_vars *vars, float angle)
{
	vars->player->radians = add_radians(vars->player->radians, angle);
	draw_map(vars->map_img, vars->map, vars->player);
	draw_player(vars->map_img, vars->player, vars->map);
	raycast3d(vars);
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (keydata.key == MLX_KEY_W
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		move_player(vars, 1, 0);
	if (keydata.key == MLX_KEY_S
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		move_player(vars, -1, 0);
	if (keydata.key == MLX_KEY_A
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		move_player(vars, -1, M_PI / 2);
	if (keydata.key == MLX_KEY_D
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		move_player(vars, 1, M_PI / 2);
	if (keydata.key == MLX_KEY_LEFT
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		rotate_player(vars, -0.1);
	if (keydata.key == MLX_KEY_RIGHT
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		rotate_player(vars, 0.1);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		my_mlx_close(vars);
}
