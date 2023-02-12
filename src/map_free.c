/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:24:21 by sdukic            #+#    #+#             */
/*   Updated: 2023/02/12 18:00:24 by sdukic           ###   ########.fr       */
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

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	map_destructor(t_map *map)
{
	free_2d_array(map->mini_map);
	free_2d_array(map->south_texture.texture);
	free_2d_array(map->north_texture.texture);
	free_2d_array(map->east_texture.texture);
	free_2d_array(map->west_texture.texture);
}
