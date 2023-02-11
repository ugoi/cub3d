#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/gnl/get_next_line.h"
#include "../../lib/libft/libft.h"

#include "parser.h"

int	is_left_wall_valid(char *tmp_map)
{
	char **split = ft_wall_split(tmp_map, '\n');
	if (!split)
	{
		printf("Error\nMap content has unwanted new lines\n");
		return (0);
	}
	int	i;
	int	j;

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
