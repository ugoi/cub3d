/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_module.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:10:52 by stefan            #+#    #+#             */
/*   Updated: 2023/02/13 07:03:36 by bogunlan         ###   ########.fr       */
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

float	get_dir_from_key(int key)
{
	float	dir;

	dir = 0;
	if (key == MLX_KEY_W)
		dir = 0;
	if (key == MLX_KEY_S)
		dir = M_PI;
	if (key == MLX_KEY_A)
		dir = 3 * M_PI / 2;
	if (key == MLX_KEY_D)
		dir = M_PI / 2;
	if (key == MLX_KEY_LEFT)
		dir = -0.1;
	if (key == MLX_KEY_RIGHT)
		dir = 0.1;
	return (dir);
	return (0);
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_vars	*vars;
	float	dir;

	vars = (t_vars *)param;
	dir = get_dir_from_key(keydata.key);
	if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S
		|| keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D)
		move_player(1, dir, vars->player, *vars->map);
	if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)
		rotate_player(dir, vars->player);
	if (keydata.key == MLX_KEY_ESCAPE)
		my_mlx_close(vars);
	draw_map(vars->map_img, vars->map, vars->player);
	draw_player(vars->map_img, vars->player, vars->map);
	raycast3d(vars);
}

int32_t	init_window(t_map *map, t_player *player)
{
	t_vars		vars;

	init_vars(&vars, map, player);
	draw_main(vars.main_img, vars.map->floor_color, vars.map->ceiling_color);
	draw_map(vars.map_img, map, player);
	if (mlx_image_to_window(vars.mlx, vars.main_img, 0, 0) < 0)
		error();
	if (mlx_image_to_window(vars.mlx, vars.map_img, 0, 0) < 0)
		error();
	draw_map(vars.map_img, vars.map, vars.player);
	draw_player(vars.map_img, vars.player, vars.map);
	raycast3d(&vars);
	mlx_key_hook(vars.mlx, my_keyhook, &vars);
	mlx_close_hook(vars.mlx, my_mlx_close, &vars);
	mlx_loop(vars.mlx);
	mlx_delete_image(vars.mlx, vars.map_img);
	mlx_delete_image(vars.mlx, vars.main_img);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}
