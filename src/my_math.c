/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 01:46:40 by stefan            #+#    #+#             */
/*   Updated: 2023/02/12 18:51:32 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/my_math.h"
#include <math.h>
#include "MLX42.h"
#include <stdlib.h>
#include"./include/colors.h"

t_int_vector	get_scaled_pos(t_float_vector pos, int scaling_factor)
{
	t_int_vector	scaled_player_pos;

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

t_float_vector	add_vectors(t_float_vector v1, t_float_vector v2)
{
	t_float_vector	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	return (result);
}

void	init_draw_vector(t_draw_vector_params *p, t_int_vector start,
	t_int_vector end)
{
	p->color = get_rgba(0, 0, 255, 255);
	p->width = 2;
	p->half_width = p->width / 2;
	p->x = start.x;
	p->y = start.y;
	p->dx = abs(end.x - start.x);
	p->dy = abs(end.y - start.y);
	if (start.x < end.x)
		p->sx = 1;
	else
		p->sx = -1;
	if (start.y < end.y)
		p->sy = 1;
	else
		p->sy = -1;
	if (p->dx > p->dy)
		p->err = p->dx / 2;
	else
		p->err = -p->dy / 2;
}

int	draw_vector(mlx_image_t *img, t_int_vector start, t_int_vector end)
{
	t_draw_vector_params	p;
	int						i;

	init_draw_vector(&p, start, end);
	while (1)
	{
		i = -p.half_width;
		while (i <= p.half_width)
			mlx_put_pixel(img, p.x + i++, p.y, p.color);
		if (p.x == end.x && p.y == end.y)
			break ;
		p.e2 = p.err;
		if (p.e2 > -p.dx)
		{
			p.err -= p.dy;
			p.x += p.sx;
		}
		if (p.e2 < p.dy)
		{
			p.err += p.dx;
			p.y += p.sy;
		}
	}
	return (0);
}
