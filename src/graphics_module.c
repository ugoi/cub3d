/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_module.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:10:52 by stefan            #+#    #+#             */
/*   Updated: 2023/02/07 20:01:18 by sdukic           ###   ########.fr       */
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
	uint32_t x = 0;
	uint32_t y = 0;
	while (y < main_img->height)
	{
		while (x < main_img->width)
		{
			if (y < main_img->height / 2)
				mlx_put_pixel(main_img, x, y, get_rgba(BLUE));
			else
				mlx_put_pixel(main_img, x, y, get_rgba(GRAY));
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

void draw_columns(mlx_image_t *img, int n, float w, int start, int end, uint32_t color)
{
	int i;
	int j;

	i = start;
	while (i < end)
	{
		j = 0;
		while (j < w)
		{
			mlx_put_pixel(img, n * w + j, i, color);
			j++;
		}
		i++;
	}
}

// void draw_columns_with_texture(mlx_image_t *img, int n, float w, int start, int end, t_float_vector ray_pos, t_texture texture)
// {
// 	int i;
// 	int j;
// 	int texture_x;
// 	int texture_y;
// 	uint32_t color;
// 	int is_horizontal;
// 	t_int_vector uncapped_start_end;
// 	int ty_offset;
// 	// int ty_step;

// 	// ty_step = texture.dimensions.y / (end - start);
// 	ty_offset = 0;
// 	uncapped_start_end.x = start;
// 	uncapped_start_end.y = end;
// 	if (start < 0)
// 		start = 0;
// 	if (end > (int)img->height)
// 	{
// 		end = (int)img->height;
// 		ty_offset = ((uncapped_start_end.y - uncapped_start_end.x) - (end - start)) / 2;
// 	}

// 	if (fmod(ray_pos.x, 1.0) == 0)
// 		is_horizontal = 0;
// 	else
// 		is_horizontal = 1;
// 	i = start;
// 	while (i < end)
// 	{
// 		j = 0;
// 		while (j < w)
// 		{
// 			if (is_horizontal)
// 			{
// 				texture_x = (int)(ray_pos.x * texture.dimensions.x) % texture.dimensions.x;
// 				// texture_y = (int)(ray_pos.y * texture.dimensions.y) % texture.dimensions.y;
// 				texture_y = (int)(texture.dimensions.y * (i - start + ty_offset) / (uncapped_start_end.y - uncapped_start_end.x));
// 				if (texture.texture[texture_y][texture_x] == '0')
// 					color = get_rgba(BLACK);
// 				else if (texture.texture[texture_y][texture_x] == '1')
// 					color = get_rgba(WHITE);
// 				mlx_put_pixel(img, n * w + j, i, color);
// 			}
// 			else
// 			{
// 				texture_x = (int)(ray_pos.y * texture.dimensions.x) % texture.dimensions.x;
// 				// texture_y = (int)(ray_pos.y * texture.dimensions.y) % texture.dimensions.y;
// 				texture_y = (int)(texture.dimensions.y * (i - start + ty_offset) / (uncapped_start_end.y - uncapped_start_end.x));
// 				if (texture.texture[texture_y][texture_x] == '0')
// 					color = get_rgba(BLACK);
// 				else if (texture.texture[texture_y][texture_x] == '1')
// 					color = get_rgba(WHITE);
// 				mlx_put_pixel(img, n * w + j, i, color);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

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

void draw_columns_with_texture(mlx_image_t *img, int n, float w, int start, int end, t_ray ray, t_texture texture)
{
	int i;
	int j;
	int texture_x;
	int texture_y;
	uint32_t color;
	int is_vertical;
	t_int_vector uncapped_start_end;
	int ty_offset;
	t_float_vector ray_pos;
	// int ty_step;

	// ty_step = texture.dimensions.y / (end - start);
	ray_pos.x = ray.origin.x + ray.ray_vector.x;
	ray_pos.y = ray.origin.y + ray.ray_vector.y;
	ty_offset = 0;
	uncapped_start_end.x = start;
	uncapped_start_end.y = end;
	if (start < 0)
		start = 0;
	if (end > (int)img->height)
	{
		end = (int)img->height;
		ty_offset = ((uncapped_start_end.y - uncapped_start_end.x) - (end - start)) / 2;
	}

	if (ray.type == NORTH || ray.type == SOUTH)
		is_vertical = 1;
	else
		is_vertical = 0;
	i = start;
	while (i < end)
	{
		j = 0;
		while (j < w)
		{
			if (is_vertical)
			{
				texture_x = (int)(ray_pos.x * texture.dimensions.x) % texture.dimensions.x;
				// texture_y = (int)(ray_pos.y * texture.dimensions.y) % texture.dimensions.y;
				texture_y = (int)(texture.dimensions.y * (i - start + ty_offset) / (uncapped_start_end.y - uncapped_start_end.x));
				if (texture.texture[texture_y][texture_x] == '0')
					color = get_rgba(BLACK);
				else if (texture.texture[texture_y][texture_x] == '1')
					color = get_rgba(WHITE);
				mlx_put_pixel(img, n * w + j, i, color);
			}
			else
			{
				texture_x = (int)(ray_pos.y * texture.dimensions.x) % texture.dimensions.x;
				// texture_y = (int)(ray_pos.y * texture.dimensions.y) % texture.dimensions.y;
				texture_y = (int)(texture.dimensions.y * (i - start + ty_offset) / (uncapped_start_end.y - uncapped_start_end.x));
				if (texture.texture[texture_y][texture_x] == '0')
					color = get_rgba(BLACK);
				else if (texture.texture[texture_y][texture_x] == '1')
					color = get_rgba(WHITE);
				mlx_put_pixel(img, n * w + j, i, color);
			}
			j++;
		}
		i++;
	}
}

void raycast3D(t_vars *vars)
{
	int				i;
	float			ray_angle;
	float				scaling_factor;
	int				dof;
	t_int_vector	scaled_player_pos;
	t_float_vector	offset;
	t_int_vector	ray_pos_in_map;

	t_float_vector	horizontal_ray_pos;
	float			horizontal_distance;

	t_float_vector	vertical_ray_pos;
	float			vertical_distance;

	t_float_vector	shortest_ray_pos;
	float			shortest_distance;

	t_ray			ray;

	int 			wall_color;
	t_texture		texture;

	scaling_factor = vars->map->minimap_scaling_factor;
	scaled_player_pos = get_scaled_pos(vars->player->pos, scaling_factor);

	ray_angle = add_radians(vars->player->radians, -FOV/2 * DEG_TO_RAD);
	i = 0;
	draw_main(vars->main_img);
	while (i < FOV / RESOLUTION)
	{
		horizontal_distance = 0;
		vertical_distance = 0;
		shortest_distance = 0;
		ray_angle = add_radians(ray_angle, DEG_TO_RAD * RESOLUTION);

		//Check horizontal lines
		dof = 0;
		if (ray_angle < M_PI)
		{
			horizontal_ray_pos.y = ceilf(vars->player->pos.y);
			horizontal_ray_pos.x = vars->player->pos.x + (horizontal_ray_pos.y - vars->player->pos.y) / tanf(ray_angle);
			offset.y = 1;
			offset.x = offset.y / tanf(ray_angle);
		}
		else
		{
			horizontal_ray_pos.y = floorf(vars->player->pos.y);
			horizontal_ray_pos.x = vars->player->pos.x + (horizontal_ray_pos.y - vars->player->pos.y) / tanf(ray_angle);
			offset.y = -1;
			offset.x = offset.y / tanf(ray_angle);
		}
		if (ray_angle == 0 || ray_angle == M_PI)
		{
			horizontal_ray_pos = vars->player->pos;
			offset.x = 0;
			offset.y = 0;
		}

		while (dof < 8)
		{
			if (offset.y < 0)
				ray_pos_in_map.y = (int)horizontal_ray_pos.y - 1;
			else
				ray_pos_in_map.y = (int)horizontal_ray_pos.y;
			ray_pos_in_map.x = (int)horizontal_ray_pos.x;
			if (ray_pos_in_map.x < vars->map->raw_map_dimensions.x && ray_pos_in_map.x >= 0 && ray_pos_in_map.y < vars->map->raw_map_dimensions.y && ray_pos_in_map.y >= 0 && vars->map->raw_map[ray_pos_in_map.y][ray_pos_in_map.x] == '1')
			{
				horizontal_distance = hypotf(vars->player->pos.x - horizontal_ray_pos.x, vars->player->pos.y - horizontal_ray_pos.y);
				break;
			}
			else
			{
				horizontal_ray_pos.x += offset.x;
				horizontal_ray_pos.y += offset.y;
			}
			dof++;
		}

		//Check vertical lines
		dof = 0;
		if (ray_angle < M_PI / 2 || ray_angle > 3 * M_PI / 2)
		{
			vertical_ray_pos.x = ceilf(vars->player->pos.x);
			vertical_ray_pos.y = vars->player->pos.y + (vertical_ray_pos.x - vars->player->pos.x) * tanf(ray_angle);
			offset.x = 1;
			offset.y = offset.x * tanf(ray_angle);
		}
		else
		{
			vertical_ray_pos.x = floorf(vars->player->pos.x);
			vertical_ray_pos.y = vars->player->pos.y + (vertical_ray_pos.x - vars->player->pos.x) * tanf(ray_angle);
			offset.x = -1;
			offset.y = offset.x * tanf(ray_angle);
		}
		if (ray_angle == M_PI / 2 || ray_angle == 3 * M_PI / 2)
		{
			vertical_ray_pos.x = vars->player->pos.x;
			vertical_ray_pos.y = vars->player->pos.y;
			offset.x = 0;
			offset.y = 0;
		}

		while (dof < 8)
		{
			if (offset.x < 0)
				ray_pos_in_map.x = (int)vertical_ray_pos.x - 1;
			else
				ray_pos_in_map.x = (int)vertical_ray_pos.x;
			ray_pos_in_map.y = (int)vertical_ray_pos.y;
			if (ray_pos_in_map.x < vars->map->raw_map_dimensions.x && ray_pos_in_map.y >= 0 && ray_pos_in_map.y < vars->map->raw_map_dimensions.y && ray_pos_in_map.x >= 0 && vars->map->raw_map[ray_pos_in_map.y][ray_pos_in_map.x] == '1')
			{
				vertical_distance = hypotf(vars->player->pos.x - vertical_ray_pos.x, vars->player->pos.y - vertical_ray_pos.y);
				break;
			}
			else
			{
				vertical_ray_pos.x += offset.x;
				vertical_ray_pos.y += offset.y;
			}
			dof++;
		}

		//Get shortest ray
		if ((horizontal_distance <= vertical_distance || vertical_distance <= 0) && horizontal_distance > 0)
		{
			shortest_distance = horizontal_distance;
			shortest_ray_pos = horizontal_ray_pos;
			wall_color = get_rgba(RED);
		}
		else
		{
			shortest_distance = vertical_distance;
			shortest_ray_pos = vertical_ray_pos;
			wall_color = get_rgba(DARK_RED);
		}

		ray.dest = shortest_ray_pos;
		ray.origin = vars->player->pos;
		ray.ray_vector.x = ray.dest.x - ray.origin.x;
		ray.ray_vector.y = ray.dest.y - ray.origin.y;
		ray.type = get_ray_type(ray);

		if (ray.type == NORTH)
			texture = vars->map->north_texture;
		else if (ray.type == SOUTH)
			texture = vars->map->south_texture;
		else if (ray.type == EAST)
			texture = vars->map->east_texture;
		else if (ray.type == WEST)
			texture = vars->map->west_texture;
		//Draw 2D map
		draw_vector(vars->map_img, scaled_player_pos, get_scaled_pos(shortest_ray_pos, scaling_factor), get_rgba(BLUE), 2);

		//Draw 3D walls
		float ca=add_radians(vars->player->radians, -ray_angle); shortest_distance=shortest_distance*cos(ca);                            //fix fisheye
		float line_height = 400.0 / shortest_distance;
		float wall_width = (float)vars->main_img->width / (FOV / RESOLUTION);
		int line_start = vars->main_img->height / 2 - line_height / 2;
		int line_end = vars->main_img->height / 2 + line_height / 2;
		// draw_columns(vars->main_img, i, wall_width, line_start, line_end, wall_color);
		draw_columns_with_texture(vars->main_img, i, wall_width, line_start, line_end, ray, texture);
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
		exit(0);
}

int32_t	init_window(t_map *map, t_player *player)
{
	t_vars		vars;

	vars.map = map;
	vars.player = player;
	vars.mlx = mlx_init(WIDTH, HEIGHT, "Test", false);
	if (!vars.mlx)
		error();
	vars.main_img = mlx_new_image(vars.mlx, vars.mlx->width, vars.mlx->height);
	if (!vars.main_img)
		error();
	draw_main(vars.main_img);
	if (mlx_image_to_window(vars.mlx, vars.main_img, 0, 0) < 0)
		error();
	vars.map_img = mlx_new_image(vars.mlx, WIDTH / 4, WIDTH / 4);
	if (!vars.map_img)
		error();
	draw_map(vars.map_img, map, player);
	if (mlx_image_to_window(vars.mlx, vars.map_img, 0, 0) < 0)
		error();
	mlx_key_hook(vars.mlx, my_keyhook, &vars);
	mlx_loop(vars.mlx);
	mlx_delete_image(vars.mlx, vars.map_img);
	mlx_delete_image(vars.mlx, vars.main_img);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}
