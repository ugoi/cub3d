/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 01:26:24 by stefan            #+#    #+#             */
/*   Updated: 2023/02/09 12:16:49 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/map.h"
#include "./include/player.h"
#include <math.h>

int player_constructor(char **map, t_player *player)
{
	int			i;
	int			j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
			{
				player->pos.y = i;
				player->pos.x = j;
				if (map[i][j] == 'N')
					player->radians = 3.0 / 2.0 * M_PI;
				else if (map[i][j] == 'S')
					player->radians = M_PI / 2.0;
				else if (map[i][j] == 'W')
					player->radians = M_PI;
				else if (map[i][j] == 'E')
					player->radians = 0;
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
