/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:24:21 by sdukic            #+#    #+#             */
/*   Updated: 2023/02/13 23:26:53 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/map.h"
#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "MLX42.h"
#include "./include/player.h"
#include "./include/colors.h"
#include "./include/my_math.h"
#include "../lib/libft/libft.h"
#include "./include/my_error.h"
#include <math.h>

t_int_vector	get_map_dimesnions(char **map)
{
	int				i;
	t_int_vector	dim;

	dim.x = 0;
	dim.y = 0;
	i = 0;
	while (map[i] != NULL)
	{
		dim.y++;
		dim.x = fmaxf(dim.x, (int)ft_strlen(map[i]));
		i++;
	}
	return (dim);
}

void	copy_to_scaled_map(char **scaled_map, char **map, int scaling_factor,
	t_int_vector dim)
{
	t_4d_vector		p;

	p.x = 0;
	while (p.x < dim.y)
	{
		p.y = 0;
		while (p.y < (int)ft_strlen(map[p.x]))
		{
			p.z = p.x * scaling_factor;
			while (p.z < (p.x + 1) * scaling_factor)
			{
				p.w = p.y * scaling_factor;
				while (p.w < (p.y + 1) * scaling_factor)
				{
					scaled_map[p.z][p.w] = map[p.x][p.y];
					p.w++;
				}
				p.z++;
			}
			p.y++;
		}
		p.x++;
	}
}

char	**scale_map(char **map, int scaling_factor)
{
	int				i;
	char			**scaled_map;
	t_int_vector	dim;

	dim = get_map_dimesnions(map);
	scaled_map = (char **)malloc(sizeof(char *) * (dim.y * scaling_factor + 1));
	i = 0;
	while (i < dim.y * scaling_factor)
	{
		scaled_map[i] = (char *)malloc(sizeof(char)
				* (dim.x * scaling_factor + 1));
		i++;
	}
	scaled_map[dim.y * scaling_factor] = NULL;
	i = 0;
	while (i < dim.y * scaling_factor)
	{
		memset(scaled_map[i], '0', dim.x * scaling_factor);
		scaled_map[i][dim.x * scaling_factor] = '\0';
		i++;
	}
	copy_to_scaled_map(scaled_map, map, scaling_factor, dim);
	return (scaled_map);
}

float	get_fscaling_factor(t_int_vector raw_dimensions,
	t_int_vector scaled_dimensions)
{
	t_float_vector	scaling_factors;
	float			scaling_factor;

	scaling_factors.x = (float)scaled_dimensions.x / (float)raw_dimensions.x;
	scaling_factors.y = (float)scaled_dimensions.y / (float)raw_dimensions.y;
	scaling_factor = fminf(scaling_factors.x, scaling_factors.y);
	return (scaling_factor);
}

void	map_constructor(t_map *map, t_map_parsing *map_parsing)
{
	map->raw_map = map_parsing->cub3d_map;
	map->floor_color = get_rgba(map_parsing->textures.floor1,
			map_parsing->textures.floor2, map_parsing->textures.floor3, 255);
	map->ceiling_color = get_rgba(map_parsing->textures.ceiling1, map_parsing
			->textures.ceiling2, map_parsing->textures.ceiling3, 255);
	map->raw_map = remove_newlines(map->raw_map);
	map->raw_map_dimensions = get_map_dimesnions(map->raw_map);
	map->south_texture.texture = init_texture(map_parsing->textures.south_path);
	map->south_texture.dimensions = get_map_dimesnions(
			map->south_texture.texture);
	map->north_texture.texture = init_texture(map_parsing->textures.north_path);
	map->north_texture.dimensions = get_map_dimesnions(
			map->north_texture.texture);
	map->east_texture.texture = init_texture(map_parsing->textures.east_path);
	map->east_texture.dimensions = get_map_dimesnions(
			map->east_texture.texture);
	map->west_texture.texture = init_texture(map_parsing->textures.west_path);
	parser_cleaner(map_parsing);
	map->west_texture.dimensions = get_map_dimesnions(
			map->west_texture.texture);
	map->minimap_dimensions = (t_int_vector){WIDTH / 4, WIDTH / 4};
	map->minimap_scaling_factor = get_fscaling_factor(
			map->raw_map_dimensions, map->minimap_dimensions);
	map->mini_map = scale_map(map->raw_map, map->minimap_scaling_factor);
}
