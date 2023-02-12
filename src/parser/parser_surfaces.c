/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_surfaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:54:54 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/12 21:54:56 by bogunlan         ###   ########.fr       */
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

int	floor_val_is_valid(t_map_parsing *map, char **split_vals)
{
	int	error;

	error = no_errors;
	if (split_count(split_vals) != 3)
		error = elements_error;
	else
	{
		if (set_floor_vals(map, split_vals) != no_errors)
			error = elements_error;
	}
	return (error);
}

int	parse_map_floor(char *vals, t_map_parsing *map)
{
	char	*tmp_floor;
	char	**split_vals;
	int		error;

	tmp_floor = ft_substr(vals, 0, ft_strlen(vals) - 1);
	if (check_comma_separator(tmp_floor) != no_errors)
		return (elements_error);
	split_vals = ft_split(tmp_floor, ',');
	if (split_count(split_vals) != 3)
		return (elements_error);
	if (!split_vals)
	{
		free(tmp_floor);
		return (elements_error);
	}
	error = floor_val_is_valid(map, split_vals);
	free(tmp_floor);
	ft_free(split_vals);
	if (error)
		return (error);
	return (no_errors);
}

int	ceiling_val_is_valid(t_map_parsing *map, \
char **split_vals, char *tmp_ceiling)
{
	int	error;

	error = no_errors;
	if (split_count(split_vals) != 3)
		error = elements_error;
	else
	{
		if (set_ceiling_vals(map, split_vals) != no_errors)
			error = elements_error;
		ft_free(split_vals);
		free(tmp_ceiling);
	}
	return (error);
}

int	parse_map_ceiling(char *vals, t_map_parsing *map)
{
	char	*tmp_ceiling;
	char	**split_vals;
	int		error;

	tmp_ceiling = ft_substr(vals, 0, ft_strlen(vals) - 1);
	if (check_comma_separator(tmp_ceiling) != no_errors)
		return (elements_error);
	split_vals = ft_split(tmp_ceiling, ',');
	if (!split_vals)
	{
		free(tmp_ceiling);
		return (elements_error);
	}
	error = ceiling_val_is_valid(map, split_vals, tmp_ceiling);
	if (error)
		return (error);
	return (no_errors);
}
