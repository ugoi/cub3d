/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:10:52 by stefan            #+#    #+#             */
/*   Updated: 2023/02/12 19:04:06 by sdukic           ###   ########.fr       */
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

int	draw_main(mlx_image_t *main_img, int floor_color, int ceiling_color)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;

	y = 0;
	while (y < main_img->height)
	{
		x = 0;
		while (x < main_img->width)
		{
			if (y < main_img->height / 2)
				color = ceiling_color;
			else
				color = floor_color;
			mlx_put_pixel(main_img, x, y, color);
			x++;
		}
		y++;
	}
	return (0);
}

void	draw_columns_with_texture(mlx_image_t *img, t_texdim d,
	t_ray ray, t_texture texture)
{
	t_int_vector	i;
	t_int_vector	texture_iter;
	uint32_t		color;
	int				ty_offset;
	int				height;

	height = d.end - d.start;
	d.start = fmaxf(d.start, 0);
	d.end = fminf(d.end, (int)img->height);
	ty_offset = (height - height * (d.end - d.start) / height) / 2;
	i.x = d.start;
	while (i.x < d.end)
	{
		i.y = 0;
		while (i.y < d.w)
		{
			texture_iter = calculate_texture(ray, texture,
					((float)i.x - (float)d.start + (float)ty_offset)
					/ ((float)height));
			color = get_color_from_texture(texture, texture_iter);
			mlx_put_pixel(img, d.n * d.w + i.y, i.x, color);
			i.y++;
		}
		i.x++;
	}
}

void	draw_3d_walls(t_vars *vars, t_ray shortest_ray, int i,
	t_texture texture)
{
	float	ca;
	float	line_height;
	float	wall_width;
	int		line_start;
	int		line_end;

	ca = add_radians(vars->player->radians, -shortest_ray.angle);
	shortest_ray.distance = shortest_ray.distance * cos(ca);
	line_height = 400.0 / shortest_ray.distance;
	wall_width = (float)vars->main_img->width / (FOV / RESOLUTION);
	line_start = vars->main_img->height / 2 - line_height / 2;
	line_end = vars->main_img->height / 2 + line_height / 2;
	draw_columns_with_texture(vars->main_img, (t_texdim){i, wall_width,
		line_start, line_end}, shortest_ray, texture);
}
