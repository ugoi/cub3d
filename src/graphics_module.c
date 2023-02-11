/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_module.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:10:52 by stefan            #+#    #+#             */
/*   Updated: 2023/02/11 21:34:30 by sdukic           ###   ########.fr       */
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

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

int	draw_main(mlx_image_t *main_img)
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
				color = get_rgba(BLUE);
			else
				color = get_rgba(GRAY);
			mlx_put_pixel(main_img, x, y, color);
			x++;
		}
		y++;
	}
	return (0);
}

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

	color = get_rgba(BLACK);
	if (texture.texture[texture_iter.y][texture_iter.x] == '0')
		color = get_rgba(BLACK);
	else if (texture.texture[texture_iter.y][texture_iter.x] == '1')
		color = get_rgba(WHITE);
	return (color);
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
	d.start = max(d.start, 0);
	d.end = min(d.end, (int)img->height);
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
		if (ray.dest_in_map.x < vars->map->raw_map_dimensions.x
			&& ray.dest_in_map.x >= 0
			&& ray.dest_in_map.y < vars->map->raw_map_dimensions.y
			&& ray.dest_in_map.y >= 0
			&& vars->map->raw_map[ray.dest_in_map.y]
			[ray.dest_in_map.x] == '1')
			break ;
		else
			ray.dest = add_vectors(ray.dest, ray.offset);
		dof++;
	}
	return (ray.dest);
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
		if (ray.dest_in_map.x < vars->map->raw_map_dimensions.x
			&& ray.dest_in_map.y >= 0
			&& ray.dest_in_map.y < vars->map->raw_map_dimensions.y
			&& ray.dest_in_map.x >= 0
			&& vars->map->raw_map[ray.dest_in_map.y][ray.dest_in_map.x] == '1')
			break ;
		else
			ray.dest = add_vectors(ray.dest, ray.offset);
		dof++;
	}
	return (ray.dest);
}

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
		= add_radians(vars->player->radians, -FOV/2 * DEG_TO_RAD);
	vertical_ray->angle
		= add_radians(vars->player->radians, -FOV/2 * DEG_TO_RAD);
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

void	draw_3D_walls(t_vars *vars, t_ray shortest_ray, int i,
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

void	raycast3D(t_vars *vars)
{
	int				i;
	t_ray			s_ray;
	t_ray			h_ray;
	t_ray			v_ray;
	t_texture		texture;

	init_start_angle_andplayer_pos(vars, &h_ray, &v_ray);
	i = 0;
	draw_main(vars->main_img);
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
		draw_3D_walls(vars, s_ray, i, texture);
		i++;
	}
}

void	move_player_up(t_vars *vars)
{
	float			collision_distance;
	t_float_vector	collision_point;

	collision_distance = 0.11;
	collision_point.x = vars->player->pos.x
		+ collision_distance * cos(vars->player->radians);
	collision_point.y = vars->player->pos.y
		+ collision_distance * sin(vars->player->radians);
	if (vars->map->raw_map[(int)vars->player->pos.y]
		[(int)collision_point.x] != '1')
		vars->player->pos.x += 0.1 * cos(vars->player->radians);
	if (vars->map->raw_map[(int)collision_point.y]
		[(int)vars->player->pos.x] != '1')
		vars->player->pos.y += 0.1 * sin(vars->player->radians);
	draw_map(vars->map_img, vars->map, vars->player);
	draw_player(vars->map_img, vars->player, vars->map);
	raycast3D(vars);
}

void	move_player_down(t_vars *vars)
{
	float			collision_distance;
	t_float_vector	collision_point;

	collision_distance = 0.11;
	collision_point.x = vars->player->pos.x
		- collision_distance * cos(vars->player->radians);
	collision_point.y = vars->player->pos.y
		- collision_distance * sin(vars->player->radians);
	if (vars->map->raw_map[(int)vars->player->pos.y]
		[(int)collision_point.x] != '1')
		vars->player->pos.x -= 0.1 * cos(vars->player->radians);
	if (vars->map->raw_map[(int)collision_point.y]
		[(int)vars->player->pos.x] != '1')
		vars->player->pos.y -= 0.1 * sin(vars->player->radians);
	draw_map(vars->map_img, vars->map, vars->player);
	draw_player(vars->map_img, vars->player, vars->map);
	raycast3D(vars);
}

void	move_player_left(t_vars *vars)
{
	float			collision_distance;
	t_float_vector	collision_point;

	collision_distance = 0.11;
	collision_point.x = vars->player->pos.x
		- collision_distance * cos(vars->player->radians + M_PI / 2);
	collision_point.y = vars->player->pos.y
		- collision_distance * sin(vars->player->radians + M_PI / 2);
	if (vars->map->raw_map[(int)vars->player->pos.y]
		[(int)collision_point.x] != '1')
		vars->player->pos.x -= 0.1 * cos(vars->player->radians + M_PI / 2);
	if (vars->map->raw_map[(int)collision_point.y]
		[(int)vars->player->pos.x] != '1')
		vars->player->pos.y -= 0.1 * sin(vars->player->radians + M_PI / 2);
	draw_map(vars->map_img, vars->map, vars->player);
	draw_player(vars->map_img, vars->player, vars->map);
	raycast3D(vars);
}

void	move_player_right(t_vars *vars)
{
	float			collision_distance;
	t_float_vector	collision_point;

	collision_distance = 0.11;
	collision_point.x = vars->player->pos.x
		+ collision_distance * cos(vars->player->radians + M_PI / 2);
	collision_point.y = vars->player->pos.y
		+ collision_distance * sin(vars->player->radians + M_PI / 2);
	if (vars->map->raw_map[(int)vars->player->pos.y]
		[(int)collision_point.x] != '1')
		vars->player->pos.x += 0.1 * cos(vars->player->radians + M_PI / 2);
	if (vars->map->raw_map[(int)collision_point.y]
		[(int)vars->player->pos.x] != '1')
		vars->player->pos.y += 0.1 * sin(vars->player->radians + M_PI / 2);
	draw_map(vars->map_img, vars->map, vars->player);
	draw_player(vars->map_img, vars->player, vars->map);
	raycast3D(vars);
}

void	rotate_player_left(t_vars *vars)
{
	vars->player->radians = add_radians(vars->player->radians, -0.1);
	draw_map(vars->map_img, vars->map, vars->player);
	draw_player(vars->map_img, vars->player, vars->map);
	raycast3D(vars);
}

void	rotate_player_right(t_vars *vars)
{
	vars->player->radians = add_radians(vars->player->radians, 0.1);
	draw_map(vars->map_img, vars->map, vars->player);
	draw_player(vars->map_img, vars->player, vars->map);
	raycast3D(vars);
}

void	my_mlx_close(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	map_destructor(vars->map);
	mlx_delete_image(vars->mlx, vars->map_img);
	mlx_delete_image(vars->mlx, vars->main_img);
	mlx_terminate(vars->mlx);
	printf("Closing window\n");
	exit(0);
}

void	my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (keydata.key == MLX_KEY_W
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		move_player_up(vars);
	if (keydata.key == MLX_KEY_S
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		move_player_down(vars);
	if (keydata.key == MLX_KEY_A
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		move_player_left(vars);
	if (keydata.key == MLX_KEY_D
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		move_player_right(vars);
	if (keydata.key == MLX_KEY_LEFT
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		rotate_player_left(vars);
	if (keydata.key == MLX_KEY_RIGHT
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		rotate_player_right(vars);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		my_mlx_close(vars);
}

void	init_vars(t_vars *vars, t_map *map, t_player *player)
{
	vars->map = map;
	vars->player = player;
	vars->mlx = mlx_init(WIDTH, HEIGHT, "Test", false);
	if (!vars->mlx)
		error();
	vars->main_img = mlx_new_image(vars->mlx,
			vars->mlx->width, vars->mlx->height);
	if (!vars->main_img)
		error();
	vars->map_img = mlx_new_image(vars->mlx, WIDTH / 4, WIDTH / 4);
	if (!vars->map_img)
		error();
}

int32_t	init_window(t_map *map, t_player *player)
{
	t_vars		vars;

	init_vars(&vars, map, player);
	draw_main(vars.main_img);
	draw_map(vars.map_img, map, player);
	if (mlx_image_to_window(vars.mlx, vars.main_img, 0, 0) < 0)
		error();
	if (mlx_image_to_window(vars.mlx, vars.map_img, 0, 0) < 0)
		error();
	draw_map(vars.map_img, vars.map, vars.player);
	draw_player(vars.map_img, vars.player, vars.map);
	raycast3D(&vars);
	mlx_key_hook(vars.mlx, my_keyhook, &vars);
	mlx_close_hook(vars.mlx, my_mlx_close, &vars);
	mlx_loop(vars.mlx);
	mlx_delete_image(vars.mlx, vars.map_img);
	mlx_delete_image(vars.mlx, vars.main_img);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}
