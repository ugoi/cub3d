/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 01:25:40 by stefan            #+#    #+#             */
/*   Updated: 2023/02/08 20:37:18 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

#include "my_math.h"

typedef struct s_player
{
	t_float_vector	pos;
	t_int_vector	scaled_pos;
	t_float_vector	dir;
	float			radians;
}				t_player;

int player_constructor(char **map, t_player *player);

#endif
