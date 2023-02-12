/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_top_wall_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:55:24 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/12 21:55:27 by bogunlan         ###   ########.fr       */
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

int	is_first_line_wall(char *tmp_map)
{
	int	i;
	int	in_map;

	i = 0;
	in_map = 0;
	while (tmp_map[i] && !in_map)
	{
		if (tmp_map[i] != '\n')
		{
			in_map = 1;
			while (in_map)
			{
				if (tmp_map[i] != '1' && tmp_map[i] != ' ' && \
				tmp_map[i] != '\n')
					return (FALSE);
				if (tmp_map[i] == '\n' || tmp_map[i] == '\0')
					break ;
				i++;
			}
		}
		i++;
	}
	return (TRUE);
}

int	get_line_after_wall(char **lines)
{
	int	i;
	int	j;

	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] == '0')
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}
