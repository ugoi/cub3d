/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:24:23 by stefan            #+#    #+#             */
/*   Updated: 2023/02/07 18:59:09 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include <stdint.h>
# include "my_math.h"

enum e_ray_type
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

typedef struct s_ray
{
	t_float_vector 	origin;
	t_float_vector 	ray_vector;
	t_float_vector 	dest;
	enum e_ray_type	type;
}				t_ray;

#endif
