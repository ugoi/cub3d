/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 01:26:24 by stefan            #+#    #+#             */
/*   Updated: 2023/02/11 00:34:28 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/map.h"
#include "./include/player.h"
#include <math.h>

bool	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (true);
	return (false);
}

void	set_player_direction(t_player *player, char c)
{
	if (c == 'N')
		player->radians = 3.0 / 2.0 * M_PI;
	else if (c == 'S')
		player->radians = M_PI / 2.0;
	else if (c == 'W')
		player->radians = M_PI;
	else if (c == 'E')
		player->radians = 0;
}

int	player_constructor(char **map, t_player *player)
{
	int			i;
	int			j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player(map[i][j]))
			{
				player->pos = (t_float_vector){(float)j + 0.5, (float)i + 0.5};
				set_player_direction(player, map[i][j]);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
