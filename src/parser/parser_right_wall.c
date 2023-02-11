#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/gnl/get_next_line.h"
#include "../../lib/libft/libft.h"

#include "parser.h"

int	is_right_wall_valid(char *tmp_map)
{
	char **split = ft_wall_split(tmp_map, '\n');
	if (!split)
	{
		printf("Error\nMap content has unwanted new lines\n");
		return (0);
	}
	int	i;
	// int	j;

	i = 0;
	while (split[i])
	{
		int	line_len = (int) ft_strlen(split[i]) - 1;
		if (split[i][line_len] != '1')
		{
			ft_free(split);
			return (FALSE);
		}
		i++;
	}
	ft_free(split);
	return (TRUE);
}
