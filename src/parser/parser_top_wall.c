#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/gnl/get_next_line.h"
#include "../../lib/libft/libft.h"

#include "parser.h"

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

void	modify_map_helper(char **split, int *in_map, int *i, int *j)
{
	while (in_map)
	{
		if (split[*i][*j] != '\0')
		{
			if (split[*i][*j + 1] != '\0' && split[*i][*j] == ' ')
			split[*i][*j] = '0';
			if (split[*i][*j + 1] == '\0' && split[*i][*j] == ' ')
				split[*i][*j] = '\0';
		}
		if (split[*i][*j] == '\0')
			in_map = 0;
		(*j)++;
	}
}

void	modify_map(char **split)
{
	int	i;
	int	j;
	int	in_map;

	i = 0;
	in_map = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j] == ' ')
			j++;
		in_map = 1;
		modify_map_helper(split, &in_map, &i, &j);
		i++;
	}
}

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
	space_end_1_index = ft_strlen(split[*x + 1]) - ft_strlen(space_end_1);
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
	space_start_1_index = ft_strlen(split[*x + 1]) - ft_strlen(space_start_1);
	return (space_start_1_index);
}

int	get_space_start_2_index(char **split, int *x)
{
	char	*space_start_2;
	int		space_start_2_index;

	space_start_2  = ft_strchr(split[*x + 1], '1');
	space_start_2_index  = ft_strlen(split[*x + 1]) - ft_strlen(space_start_2);
	return (space_start_2_index);
}

int	map_not_enclosed(t_top_wall *top_wall)
{
	if (top_wall->wall_end_1_index < top_wall->space_end_1_index || \
	top_wall->wall_end_2_index > top_wall->space_end_2_index || \
	top_wall->wall_start_1_index > top_wall->space_start_1_index || \
	(top_wall->wall_start_2_index < top_wall->space_start_2_index && \
	top_wall->wall_start_2_index != 0)
	)
		return (TRUE);
	return (FALSE);
}

int	is_map_enclosed(char **split)
{
	int			x;
	t_top_wall	top_wall;

	modify_map(split);
	top_wall.line_after_wall = get_line_after_wall(split);
	if (top_wall.line_after_wall == 0)
		return (FALSE);
	while (top_wall.line_after_wall < split_count(split) - 1)
	{
		x = top_wall.line_after_wall - 1;
		top_wall.wall_end_1_index = get_wall_end_1_index(split, &x);
		top_wall.wall_end_2_index = get_wall_end_2_index(split, &x);
		top_wall.space_end_1_index = get_space_end_1_index(split, &x);
		top_wall.space_end_2_index = get_space_end_2_index(split, &x);
		top_wall.wall_start_1_index = get_wall_start_1_index(split, &x);
		top_wall.wall_start_2_index = get_wall_start_2_index(split, &x);
		top_wall.space_start_1_index = get_space_start_1_index(split, &x);
		top_wall.space_start_2_index = get_space_start_2_index(split, &x);
		if (map_not_enclosed(&top_wall))
			return (FALSE);
		top_wall.line_after_wall++;
	}
	return (TRUE);
}

int	is_top_wall_valid(char *tmp_map)
{
	char	**split;

	if (is_first_line_wall(tmp_map) != TRUE)
		return (FALSE);
	split = ft_wall_split(tmp_map, '\n');
	if (!split)
		return (FALSE);
	if (!split[0] || !split[1])
		return (FALSE);
	if (is_map_enclosed(split) != TRUE)
	{
		ft_free(split);
		return (FALSE);
	}
	ft_free(split);
	return (TRUE);
}
