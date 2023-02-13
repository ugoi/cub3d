/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_top_wall_start.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:55:14 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/13 17:15:15 by bogunlan         ###   ########.fr       */
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

int	get_wall_start_1_index(char **split, int *x)
{
	char	*wall_start_1;
	int		wall_start_1_index;

	wall_start_1 = ft_strchr(split[*x], '1');
	wall_start_1_index = ft_strlen(split[*x]) - ft_strlen(wall_start_1);
	return (wall_start_1_index);
}

int	get_wall_start_2_index(char **split, int *x)
{
	char	*wall_start_2;
	int		wall_start_2_index;

	wall_start_2 = ft_strchr(split[*x], '0');
	if (wall_start_2 != NULL)
		wall_start_2_index = ft_strlen(split[*x]) - ft_strlen(wall_start_2);
	else
		wall_start_2_index = 0;
	return (wall_start_2_index);
}

int	get_space_start_1_index(char **split, int *x)
{
	char	*space_start_1;
	int		space_start_1_index;

	space_start_1 = ft_strchr(split[*x + 1], '0');
	if (space_start_1 != NULL)
		space_start_1_index = ft_strlen(split[*x + 1]) - \
		ft_strlen(space_start_1);
	else
		space_start_1_index = ft_strlen(split[*x + 1]);
	return (space_start_1_index);
}

int	get_space_start_2_index(char **split, int *x)
{
	char	*space_start_2;
	int		space_start_2_index;

	space_start_2 = ft_strchr(split[*x + 1], '1');
	space_start_2_index = ft_strlen(split[*x + 1]) - ft_strlen(space_start_2);
	return (space_start_2_index);
}
