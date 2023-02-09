/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_module.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:10:52 by stefan            #+#    #+#             */
/*   Updated: 2023/02/09 15:22:48 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_module.h"
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
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int	draw_main(mlx_image_t *main_img)
{
	uint32_t x;
	uint32_t y;
	uint32_t color;

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

enum e_ray_type get_ray_type(t_ray ray)
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

bool is_vertical(enum e_ray_type type)
{
	return (type == NORTH || type == SOUTH);
}


t_int_vector calculate_texture( t_ray ray, t_texture texture, float ty_ratio)
{
	t_int_vector texture_iter;

	if (is_vertical(ray.type))
		texture_iter.x = (int)(ray.dest.x * texture.dimensions.x) % texture.dimensions.x;
	else
		texture_iter.x = (int)(ray.dest.y * texture.dimensions.x) % texture.dimensions.x;
	texture_iter.y = (int)(texture.dimensions.y * (ty_ratio));
	if (ray.type == SOUTH || ray.type == WEST)
		texture_iter.x = texture.dimensions.x - texture_iter.x - 1;
	return (texture_iter);
}

uint32_t get_color_from_texture(t_texture texture, t_int_vector texture_iter)
{
	uint32_t color;

	color = get_rgba(BLACK);
	if (texture.texture[texture_iter.y][texture_iter.x] == '0')
		color = get_rgba(BLACK);
	else if (texture.texture[texture_iter.y][texture_iter.x] == '1')
		color = get_rgba(WHITE);
	return color;
}

void draw_columns_with_texture(mlx_image_t *img, int n, float w, int start, int end, t_ray ray, t_texture texture)
{
	t_int_vector i;
	t_int_vector texture_iter;
	uint32_t color;
	int ty_offset;
	int wall_height;

	wall_height = end - start;
    start = max(start, 0);
    end = min(end, (int)img->height);
    ty_offset = (wall_height - wall_height * (end - start) / wall_height) / 2;
	i.x = start;
	while (i.x < end)
	{
		i.y = 0;
		while (i.y < w)
		{
			texture_iter = calculate_texture(ray, texture, ((float)i.x - (float)start + (float)ty_offset) / ((float)wall_height));
			color = get_color_from_texture(texture, texture_iter);
			mlx_put_pixel(img, n * w + i.y, i.x, color);
			i.y++;
		}
		i.x++;
	}
}

t_texture get_ray_texture(t_ray ray, t_map map)
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

t_float_vector calculate_horizontal_ray_dest(t_vars *vars, t_ray horizontal_ray)
{
	int	dof;

	dof = 0;
	if (horizontal_ray.angle < M_PI)
	{
		horizontal_ray.dest.y = ceilf(vars->player->pos.y);
		horizontal_ray.dest.x = vars->player->pos.x + (horizontal_ray.dest.y - vars->player->pos.y) / tanf(horizontal_ray.angle);
		horizontal_ray.offset.y = 1;
		horizontal_ray.offset.x = horizontal_ray.offset.y / tanf(horizontal_ray.angle);
	}
	else
	{
		horizontal_ray.dest.y = floorf(vars->player->pos.y);
		horizontal_ray.dest.x = vars->player->pos.x + (horizontal_ray.dest.y - vars->player->pos.y) / tanf(horizontal_ray.angle);
		horizontal_ray.offset.y = -1;
		horizontal_ray.offset.x = horizontal_ray.offset.y / tanf(horizontal_ray.angle);
	}
	if (horizontal_ray.angle == 0 || horizontal_ray.angle == M_PI)
	{
		horizontal_ray.dest = vars->player->pos;
		horizontal_ray.offset = (t_float_vector){0, 0};
	}

	while (dof < 8)
	{
		if (horizontal_ray.offset.y < 0)
			horizontal_ray.dest_in_map.y = (int)horizontal_ray.dest.y - 1;
		else
			horizontal_ray.dest_in_map.y = (int)horizontal_ray.dest.y;
		horizontal_ray.dest_in_map.x = (int)horizontal_ray.dest.x;
		if (horizontal_ray.dest_in_map.x < vars->map->raw_map_dimensions.x && horizontal_ray.dest_in_map.x >= 0 && horizontal_ray.dest_in_map.y < vars->map->raw_map_dimensions.y && horizontal_ray.dest_in_map.y >= 0 && vars->map->raw_map[horizontal_ray.dest_in_map.y][horizontal_ray.dest_in_map.x] == '1')
		{
			break;
		}
		else
		{
			horizontal_ray.dest = add_vectors(horizontal_ray.dest, horizontal_ray.offset);
		}
		dof++;
	}
	return (horizontal_ray.dest);
}

t_float_vector calculate_vertical_ray_dest(t_vars *vars, t_ray vertical_ray)
{
	int dof;

	dof = 0;
	if (vertical_ray.angle < M_PI / 2 || vertical_ray.angle > 3 * M_PI / 2)
	{
		vertical_ray.dest.x = ceilf(vars->player->pos.x);
		vertical_ray.dest.y = vars->player->pos.y + (vertical_ray.dest.x - vars->player->pos.x) * tanf(vertical_ray.angle);
		vertical_ray.offset.x = 1;
		vertical_ray.offset.y = vertical_ray.offset.x * tanf(vertical_ray.angle);
	}
	else
	{
		vertical_ray.dest.x = floorf(vars->player->pos.x);
		vertical_ray.dest.y = vars->player->pos.y + (vertical_ray.dest.x - vars->player->pos.x) * tanf(vertical_ray.angle);
		vertical_ray.offset.x = -1;
		vertical_ray.offset.y = vertical_ray.offset.x * tanf(vertical_ray.angle);
	}
	if (vertical_ray.angle == M_PI / 2 || vertical_ray.angle == 3 * M_PI / 2)
	{
		vertical_ray.dest = vars->player->pos;
		vertical_ray.offset = (t_float_vector){0, 0};
	}

	while (dof < 8)
	{
		if (vertical_ray.offset.x < 0)
			vertical_ray.dest_in_map.x = (int)vertical_ray.dest.x - 1;
		else
			vertical_ray.dest_in_map.x = (int)vertical_ray.dest.x;
		vertical_ray.dest_in_map.y = (int)vertical_ray.dest.y;
		if (vertical_ray.dest_in_map.x < vars->map->raw_map_dimensions.x && vertical_ray.dest_in_map.y >= 0 && vertical_ray.dest_in_map.y < vars->map->raw_map_dimensions.y && vertical_ray.dest_in_map.x >= 0 && vars->map->raw_map[vertical_ray.dest_in_map.y][vertical_ray.dest_in_map.x] == '1')
		{
			break;
		}
		else
		{
			vertical_ray.dest = add_vectors(vertical_ray.dest, vertical_ray.offset);
		}
		dof++;
	}
	return (vertical_ray.dest);
}

t_ray get_shortest_ray(t_ray horizontal_ray, t_ray vertical_ray, t_vars *vars)
{
	t_ray shortest_ray;

	if ((horizontal_ray.distance <= vertical_ray.distance || vertical_ray.distance <= 0) && horizontal_ray.distance > 0)
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

void init_start_angle_andplayer_pos(t_vars *vars, t_ray *horizontal_ray, t_ray *vertical_ray)
{
	vars->player->scaled_pos = get_scaled_pos(vars->player->pos, vars->map->minimap_scaling_factor);
	horizontal_ray->angle = add_radians(vars->player->radians, -FOV/2 * DEG_TO_RAD);
	vertical_ray->angle = add_radians(vars->player->radians, -FOV/2 * DEG_TO_RAD);
}

void update_ray_angle_and_distance(t_ray *horizontal_ray, t_ray *vertical_ray)
{
	horizontal_ray->distance = 0;
	vertical_ray->distance = 0;
	horizontal_ray->angle = add_radians(horizontal_ray->angle, DEG_TO_RAD * RESOLUTION);
	vertical_ray->angle = add_radians(vertical_ray->angle, DEG_TO_RAD * RESOLUTION);
}

void draw_3D_walls(t_vars *vars, t_ray shortest_ray, int i, t_texture texture)
{
	float ca=add_radians(vars->player->radians, -shortest_ray.angle); shortest_ray.distance=shortest_ray.distance*cos(ca);                            //fix fisheye
	float line_height = 400.0 / shortest_ray.distance;
	float wall_width = (float)vars->main_img->width / (FOV / RESOLUTION);
	int line_start = vars->main_img->height / 2 - line_height / 2;
	int line_end = vars->main_img->height / 2 + line_height / 2;
	draw_columns_with_texture(vars->main_img, i, wall_width, line_start, line_end, shortest_ray, texture);
}

void raycast3D(t_vars *vars)
{
	int				i;
	t_ray			shortest_ray;
	t_ray			horizontal_ray;
	t_ray			vertical_ray;
	t_texture		texture;

	init_start_angle_andplayer_pos(vars, &horizontal_ray, &vertical_ray);
	i = 0;
	draw_main(vars->main_img);
	while (i < FOV / RESOLUTION)
	{
		update_ray_angle_and_distance(&horizontal_ray, &vertical_ray);
		horizontal_ray.dest = calculate_horizontal_ray_dest(vars, horizontal_ray);
		horizontal_ray.distance = hypotf(vars->player->pos.x - horizontal_ray.dest.x, vars->player->pos.y - horizontal_ray.dest.y);
		vertical_ray.dest = calculate_vertical_ray_dest(vars, vertical_ray);
		vertical_ray.distance = hypotf(vars->player->pos.x - vertical_ray.dest.x, vars->player->pos.y - vertical_ray.dest.y);
		shortest_ray = get_shortest_ray(horizontal_ray, vertical_ray, vars);
		texture = get_ray_texture(shortest_ray, *vars->map);
		draw_vector(vars->map_img, vars->player->scaled_pos, get_scaled_pos(shortest_ray.dest, vars->map->minimap_scaling_factor), get_rgba(BLUE), 2);
		draw_3D_walls(vars, shortest_ray, i, texture);
		i++;
	}
}

void move_player_up(t_vars *vars)
{
	float collision_distance = 0.11;
	t_float_vector collision_point;

	collision_point.x = vars->player->pos.x + collision_distance * cos(vars->player->radians);
	collision_point.y = vars->player->pos.y + collision_distance * sin(vars->player->radians);

	if (vars->map->raw_map[(int)vars->player->pos.y][(int)collision_point.x] != '1')
		vars->player->pos.x += 0.1 * cos(vars->player->radians);
	if (vars->map->raw_map[(int)collision_point.y][(int)vars->player->pos.x] != '1')
		vars->player->pos.y += 0.1 * sin(vars->player->radians);
	draw_map(vars->map_img, vars->map, vars->player);
	draw_player(vars->map_img, vars->player, vars->map);
	raycast3D(vars);
}

void move_player_down(t_vars *vars)
{
	float collision_distance = 0.11;
	t_float_vector collision_point;

	(void)collision_distance;
	collision_point.x = vars->player->pos.x - collision_distance * cos(vars->player->radians);
	collision_point.y = vars->player->pos.y - collision_distance * sin(vars->player->radians);

	if (vars->map->raw_map[(int)vars->player->pos.y][(int)collision_point.x] != '1')
		vars->player->pos.x -= 0.1 * cos(vars->player->radians);
	if (vars->map->raw_map[(int)collision_point.y][(int)vars->player->pos.x] != '1')
		vars->player->pos.y -= 0.1 * sin(vars->player->radians);
	draw_map(vars->map_img, vars->map, vars->player);
	draw_player(vars->map_img, vars->player, vars->map);
	raycast3D(vars);
}

void move_player_left(t_vars *vars)
{
	float collision_distance = 0.11;
	t_float_vector collision_point;

	(void)collision_distance;
	collision_point.x = vars->player->pos.x - collision_distance * cos(vars->player->radians + M_PI / 2);
	collision_point.y = vars->player->pos.y - collision_distance * sin(vars->player->radians + M_PI / 2);

	if (vars->map->raw_map[(int)vars->player->pos.y][(int)collision_point.x] != '1')
		vars->player->pos.x -= 0.1 * cos(vars->player->radians + M_PI / 2);
	if (vars->map->raw_map[(int)collision_point.y][(int)vars->player->pos.x] != '1')
		vars->player->pos.y -= 0.1 * sin(vars->player->radians + M_PI / 2);
	draw_map(vars->map_img, vars->map, vars->player);
	draw_player(vars->map_img, vars->player, vars->map);
	raycast3D(vars);
}

void move_player_right(t_vars *vars)
{
	float collision_distance = 0.11;
	t_float_vector collision_point;

	(void)collision_distance;
	collision_point.x = vars->player->pos.x + collision_distance * cos(vars->player->radians + M_PI / 2);
	collision_point.y = vars->player->pos.y + collision_distance * sin(vars->player->radians + M_PI / 2);

	if (vars->map->raw_map[(int)vars->player->pos.y][(int)collision_point.x] != '1')
		vars->player->pos.x += 0.1 * cos(vars->player->radians + M_PI / 2);
	if (vars->map->raw_map[(int)collision_point.y][(int)vars->player->pos.x] != '1')
		vars->player->pos.y += 0.1 * sin(vars->player->radians + M_PI / 2);
	draw_map(vars->map_img, vars->map, vars->player);
	draw_player(vars->map_img, vars->player, vars->map);
	raycast3D(vars);
}

void rotate_player_left(t_vars *vars)
{
	vars->player->radians = add_radians(vars->player->radians, -0.1);
	draw_map(vars->map_img, vars->map, vars->player);
	draw_player(vars->map_img, vars->player, vars->map);
	raycast3D(vars);
}

void rotate_player_right(t_vars *vars)
{
	vars->player->radians = add_radians(vars->player->radians, 0.1);
	draw_map(vars->map_img, vars->map, vars->player);
	draw_player(vars->map_img, vars->player, vars->map);
	raycast3D(vars);
}

void my_mlx_close(void *param)
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

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_vars *vars;

	vars = (t_vars*)param;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		move_player_up(vars);
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		move_player_down(vars);
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		move_player_left(vars);
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		move_player_right(vars);
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		rotate_player_left(vars);
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		rotate_player_right(vars);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		my_mlx_close(vars);
}

void init_vars(t_vars *vars, t_map *map, t_player *player)
{
	vars->map = map;
	vars->player = player;
	vars->mlx = mlx_init(WIDTH, HEIGHT, "Test", false);
	if (!vars->mlx)
		error();
	vars->main_img = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
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
