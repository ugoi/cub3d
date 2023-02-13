/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_top_wall_end.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:55:02 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/13 04:19:55 by bogunlan         ###   ########.fr       */
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

int	get_wall_end_1_index(char **split, int *x)
{
	char	*wall_end_1;
	int		wall_end_1_index;

	wall_end_1 = ft_strrchr(split[*x], '1');
	wall_end_1_index = ft_strlen(split[*x]) - ft_strlen(wall_end_1);
	return (wall_end_1_index);
}

int	get_wall_end_2_index(char **split, int *x)
{
	char	*wall_end_2;
	int		wall_end_2_index;

	wall_end_2 = ft_strrchr(split[*x], '0');
	if (wall_end_2 != NULL)
		wall_end_2_index = ft_strlen(split[*x]) - ft_strlen(wall_end_2);
	else
		wall_end_2_index = 0;
	return (wall_end_2_index);
}

int	get_space_end_1_index(char **split, int *x)
{
	char	*space_end_1;
	int		space_end_1_index;

	space_end_1 = ft_strrchr(split[*x + 1], '0');
	if (space_end_1)
		space_end_1_index = ft_strlen(split[*x + 1]) - ft_strlen(space_end_1);
	else
		space_end_1_index = 0;
	return (space_end_1_index);
}

int	get_space_end_2_index(char **split, int *x)
{
	char	*space_end_2;
	int		space_end_2_index;

	space_end_2 = ft_strrchr(split[*x + 1], '1');
	space_end_2_index = ft_strlen(split[*x + 1]) - ft_strlen(space_end_2);
	return (space_end_2_index);
}
