/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 01:46:40 by stefan            #+#    #+#             */
/*   Updated: 2023/02/07 23:14:36 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/my_math.h"
#include <math.h>
#include "MLX42.h"
#include <stdlib.h>

t_int_vector get_scaled_pos(t_float_vector pos, int scaling_factor)
{
	t_int_vector scaled_player_pos;

	scaled_player_pos.x = pos.x * scaling_factor;
	scaled_player_pos.y = pos.y * scaling_factor;
	return (scaled_player_pos);
}

float	add_radians(float radians, float radians_to_add)
{
	radians += radians_to_add;
	if (radians > 2 * M_PI)
		radians -= 2 * M_PI;
	else if (radians < 0)
		radians += 2 * M_PI;
	return (radians);
}

t_float_vector add_vectors(t_float_vector v1, t_float_vector v2)
{
	t_float_vector result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	return (result);
}

int draw_vector(mlx_image_t *img, t_int_vector start, t_int_vector end, int color, int width)
{
    int		x;
    int		y;
    int		dx;
    int		dy;
    int		sx;
    int		sy;
    int		err;
    int		e2;
    int     half_width;

    half_width = width / 2;

    x = start.x;
    y = start.y;
    dx = abs(end.x - start.x);
    dy = abs(end.y - start.y);
    sx = start.x < end.x ? 1 : -1;
    sy = start.y < end.y ? 1 : -1;
    err = (dx > dy ? dx : -dy) / 2;
    while (1)
    {
        for (int i = -half_width; i <= half_width; i++)
            mlx_put_pixel(img, x + i, y, color);
        if (x == end.x && y == end.y)
            break ;
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            x += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            y += sy;
        }
    }
    return (0);
}
