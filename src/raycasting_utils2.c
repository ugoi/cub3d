/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:54:53 by sdukic            #+#    #+#             */
/*   Updated: 2023/02/13 22:07:36 by bogunlan         ###   ########.fr       */
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
#include "./include/player.h"
#include "../lib/libft/libft.h"

t_ray	calculate_first_horizontal_ray(t_vars *vars, float angle)
{
	t_ray	ray;

	if (angle < M_PI)
	{
		ray.dest.y = ceilf(vars->player->pos.y);
		ray.dest.x = vars->player->pos.x
			+ (ray.dest.y - vars->player->pos.y) / tanf(angle);
		ray.offset.y = 1;
		ray.offset.x = ray.offset.y / tanf(angle);
	}
	else
	{
		ray.dest.y = floorf(vars->player->pos.y);
		ray.dest.x = vars->player->pos.x
			+ (ray.dest.y - vars->player->pos.y) / tanf(angle);
		ray.offset.y = -1;
		ray.offset.x = ray.offset.y / tanf(angle);
	}
	if (angle == 0 || angle == M_PI)
	{
		ray.dest = vars->player->pos;
		ray.offset = (t_float_vector){0, 0};
	}
	return (ray);
}

t_ray	calculate_first_vertical_ray(t_vars *vars, float angle)
{
	t_ray	ray;

	if (angle < M_PI / 2 || angle > 3 * M_PI / 2)
	{
		ray.dest.x = ceilf(vars->player->pos.x);
		ray.dest.y = vars->player->pos.y
			+ (ray.dest.x - vars->player->pos.x) * tanf(angle);
		ray.offset.x = 1;
		ray.offset.y = ray.offset.x * tanf(angle);
	}
	else
	{
		ray.dest.x = floorf(vars->player->pos.x);
		ray.dest.y = vars->player->pos.y
			+ (ray.dest.x - vars->player->pos.x) * tanf(angle);
		ray.offset.x = -1;
		ray.offset.y = ray.offset.x * tanf(angle);
	}
	if (angle == M_PI / 2 || angle == 3 * M_PI / 2)
	{
		ray.dest = vars->player->pos;
		ray.offset = (t_float_vector){0, 0};
	}
	return (ray);
}

t_float_vector	calculate_horizontal_ray_dest(t_vars *vars, t_ray ray)
{
	int	dof;

	ray = calculate_first_horizontal_ray(vars, ray.angle);
	dof = 0;
	while (dof < 8)
	{
		if (ray.offset.y < 0)
			ray.dest_in_map.y = (int)ray.dest.y - 1;
		else
			ray.dest_in_map.y = (int)ray.dest.y;
		ray.dest_in_map.x = (int)ray.dest.x;
		if (ray.dest_in_map.x >= vars->map->raw_map_dimensions.x || \
	ray.dest_in_map.y >= vars->map->raw_map_dimensions.y || \
	(ray.dest_in_map.y < 0 || ray.dest_in_map.x < 0 || \
	vars->map->raw_map[ray.dest_in_map.y] == NULL || \
	ray.dest_in_map.x >= ft_strlen(vars->map->raw_map[ray.dest_in_map.y]) || \
	vars->map->raw_map[ray.dest_in_map.y][ray.dest_in_map.x] == '1'))
			break ;
		else
			ray.dest = add_vectors(ray.dest, ray.offset);
		dof++;
	}
	return (ray.dest);
}

t_float_vector	calculate_vertical_ray_dest(t_vars *vars, t_ray ray)
{
	int	dof;

	ray = calculate_first_vertical_ray(vars, ray.angle);
	dof = 0;
	while (dof < 8)
	{
		if (ray.offset.x < 0)
			ray.dest_in_map.x = (int)ray.dest.x - 1;
		else
			ray.dest_in_map.x = (int)ray.dest.x;
		ray.dest_in_map.y = (int)ray.dest.y;
		if (ray.dest_in_map.x >= vars->map->raw_map_dimensions.x || \
	ray.dest_in_map.y >= vars->map->raw_map_dimensions.y || \
	(ray.dest_in_map.y < 0 || \
	ray.dest_in_map.x < 0 || \
	vars->map->raw_map[ray.dest_in_map.y] == NULL || \
	ray.dest_in_map.x >= ft_strlen(vars->map->raw_map[ray.dest_in_map.y]) || \
	vars->map->raw_map[ray.dest_in_map.y][ray.dest_in_map.x] == '1'))
			break ;
		else
			ray.dest = add_vectors(ray.dest, ray.offset);
		dof++;
	}
	return (ray.dest);
}
