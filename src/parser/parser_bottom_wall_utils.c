/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bottom_wall_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:49:25 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/12 21:49:29 by bogunlan         ###   ########.fr       */
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

int	last_line_is_valid(char *last_line)
{
	int	i;

	i = 0;
	while (last_line[i] == ' ')
		i++;
	while (last_line[i])
	{
		if (last_line[i] != '1')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	get_line_before_wall(char **lines, int index)
{
	int	i;

	while (index >= 0)
	{
		i = 0;
		while (lines[index][i])
		{
			if (lines[index][i] == '0')
				return (index);
			i++;
		}
		index--;
	}
	return (index);
}
