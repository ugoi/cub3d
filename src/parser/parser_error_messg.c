
#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/gnl/get_next_line.h"
#include "../../lib/libft/libft.h"

#include "parser.h"

void	cub3d_error_messg(int err, t_map_parsing *map)
{
	if (err == elements_error)
	{
		printf("Player positions:%d:\n", map->player_start_position);
		printf("Error\nToo many starting positions\n");
	}
	if (err == wall_error)
	{
		printf("Error\nInvalid walls\n");
	}
}
