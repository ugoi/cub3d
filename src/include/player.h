/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 01:25:40 by stefan            #+#    #+#             */
/*   Updated: 2023/02/13 00:33:57 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "my_math.h"
# include "map.h"

typedef struct s_player
{
	t_float_vector	pos;
	t_int_vector	scaled_pos;
	t_float_vector	dir;
	float			radians;
}				t_player;

int		player_constructor(char **map, t_player *player);
void	move_player(float dist, float dir, t_player *player, t_map map);
void	rotate_player(float angle, t_player *player);

#endif
