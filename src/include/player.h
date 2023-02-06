/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 01:25:40 by stefan            #+#    #+#             */
/*   Updated: 2023/02/06 02:21:16 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

#include "my_math.h"

typedef struct s_player
{
	t_float_vector	pos;
	t_float_vector	dir;
	float			radians;
}				t_player;

int player_constructor(char **map, t_player *player);

#endif