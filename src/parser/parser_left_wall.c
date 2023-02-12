/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_left_wall.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:51:08 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/12 21:51:10 by bogunlan         ###   ########.fr       */
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

int	is_left_wall_valid(char *tmp_map)
{
	char	**split;
	int		i;
	int		j;

	split = ft_wall_split(tmp_map, '\n');
	if (!split)
		return (FALSE);
	i = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j] == ' ')
			j++;
		if (split[i][j] != '1')
		{
			ft_free(split);
			return (FALSE);
		}
		i++;
	}
	ft_free(split);
	return (TRUE);
}
