/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:42:10 by sdukic            #+#    #+#             */
/*   Updated: 2023/02/12 18:44:32 by sdukic           ###   ########.fr       */
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

t_ray	get_shortest_ray(t_ray horizontal_ray, t_ray vertical_ray, t_vars *vars)
{
	t_ray	shortest_ray;

	if ((horizontal_ray.distance <= vertical_ray.distance
			|| vertical_ray.distance <= 0)
		&& horizontal_ray.distance > 0)
	{
		shortest_ray.distance = horizontal_ray.distance;
		shortest_ray.dest = horizontal_ray.dest;
	}
	else
	{
		shortest_ray.distance = vertical_ray.distance;
		shortest_ray.dest = vertical_ray.dest;
	}
	shortest_ray.origin = vars->player->pos;
	shortest_ray.ray_vector.x = shortest_ray.dest.x - shortest_ray.origin.x;
	shortest_ray.ray_vector.y = shortest_ray.dest.y - shortest_ray.origin.y;
	shortest_ray.type = get_ray_type(shortest_ray);
	shortest_ray.angle = horizontal_ray.angle;
	return (shortest_ray);
}

void	init_start_angle_andplayer_pos(t_vars *vars, t_ray *horizontal_ray,
	t_ray *vertical_ray)
{
	vars->player->scaled_pos
		= get_scaled_pos(vars->player->pos, vars->map->minimap_scaling_factor);
	horizontal_ray->angle
		= add_radians(vars->player->radians, -FOV / 2 * DEG_TO_RAD);
	vertical_ray->angle
		= add_radians(vars->player->radians, -FOV / 2 * DEG_TO_RAD);
}

void	update_ray_angle_and_distance(t_ray *horizontal_ray,
	t_ray *vertical_ray)
{
	horizontal_ray->distance = 0;
	vertical_ray->distance = 0;
	horizontal_ray->angle
		= add_radians(horizontal_ray->angle, DEG_TO_RAD * RESOLUTION);
	vertical_ray->angle
		= add_radians(vertical_ray->angle, DEG_TO_RAD * RESOLUTION);
}

void	raycast3d(t_vars *vars)
{
	int				i;
	t_ray			s_ray;
	t_ray			h_ray;
	t_ray			v_ray;
	t_texture		texture;

	init_start_angle_andplayer_pos(vars, &h_ray, &v_ray);
	i = 0;
	draw_main(vars->main_img, vars->map->floor_color, vars->map->ceiling_color);
	while (i < FOV / RESOLUTION)
	{
		update_ray_angle_and_distance(&h_ray, &v_ray);
		h_ray.dest = calculate_horizontal_ray_dest(vars, h_ray);
		h_ray.distance = hypotf(vars->player->pos.x - h_ray.dest.x,
				vars->player->pos.y - h_ray.dest.y);
		v_ray.dest = calculate_vertical_ray_dest(vars, v_ray);
		v_ray.distance = hypotf(vars->player->pos.x - v_ray.dest.x,
				vars->player->pos.y - v_ray.dest.y);
		s_ray = get_shortest_ray(h_ray, v_ray, vars);
		texture = get_ray_texture(s_ray, *vars->map);
		draw_vector(vars->map_img, vars->player->scaled_pos,
			get_scaled_pos(s_ray.dest, vars->map->minimap_scaling_factor));
		draw_3d_walls(vars, s_ray, i, texture);
		i++;
	}
}
