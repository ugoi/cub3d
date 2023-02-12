/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:54:53 by sdukic            #+#    #+#             */
/*   Updated: 2023/02/12 18:50:36 by sdukic           ###   ########.fr       */
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

enum e_ray_type	get_ray_type(t_ray ray)
{
	if (fmod(ray.dest.x, 1.0) == 0)
	{
		if (ray.ray_vector.x > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (ray.ray_vector.y > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

bool	is_vertical(enum e_ray_type type)
{
	return (type == NORTH || type == SOUTH);
}

t_int_vector	calculate_texture( t_ray ray, t_texture texture, float ty_ratio)
{
	t_int_vector	texture_iter;

	if (is_vertical(ray.type))
		texture_iter.x = (int)(ray.dest.x * texture.dimensions.x)
			% texture.dimensions.x;
	else
		texture_iter.x = (int)(ray.dest.y * texture.dimensions.x)
			% texture.dimensions.x;
	texture_iter.y = (int)(texture.dimensions.y * (ty_ratio));
	if (ray.type == SOUTH || ray.type == WEST)
		texture_iter.x = texture.dimensions.x - texture_iter.x - 1;
	return (texture_iter);
}

uint32_t	get_color_from_texture(t_texture texture, t_int_vector texture_iter)
{
	uint32_t	color;

	color = get_rgba(0, 0, 0, 255);
	if (texture.texture[texture_iter.y][texture_iter.x] == '0')
		color = get_rgba(0, 0, 0, 255);
	else if (texture.texture[texture_iter.y][texture_iter.x] == '1')
		color = get_rgba(255, 255, 255, 255);
	return (color);
}

t_texture	get_ray_texture(t_ray ray, t_map map)
{
	t_texture	texture;

	texture = map.north_texture;
	if (ray.type == NORTH)
		texture = map.north_texture;
	else if (ray.type == SOUTH)
		texture = map.south_texture;
	else if (ray.type == EAST)
		texture = map.east_texture;
	else if (ray.type == WEST)
		texture = map.west_texture;
	return (texture);
}
