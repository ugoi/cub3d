/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error_messg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:50:53 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/13 06:45:08 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/gnl/get_next_line.h"
#include "../../lib/libft/libft.h"
#include "../include/parser.h"

void	cub3d_error_messg(int err, t_map_parsing *map)
{
	if (err == map_error || err == elements_error)
	{
		printf("Error\nMap error\n");
		if (map)
		{
			if (map->player_start_position != 1)
				printf("%d players spawned\n", map->player_start_position);
		}
	}
	if (err == texture_error)
	{
		printf("Error\nTexture error\n");
	}
	if (err == wall_error)
	{
		printf("Error\nWall error\n");
	}
	if (err == file_error)
	{
		printf("Error\nNo such file or directory\n");
	}
}
