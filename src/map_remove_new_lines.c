/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_remove_new_lines.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:14:39 by sdukic            #+#    #+#             */
/*   Updated: 2023/02/12 18:14:41 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	**remove_newlines(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '\n')
				map[i][j] = 0;
			j++;
		}
		i++;
	}
	return (map);
}
