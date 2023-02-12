/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:01:27 by sdukic            #+#    #+#             */
/*   Updated: 2023/02/12 18:27:41 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/my_error.h"
#include <stdio.h>
#include <stdlib.h>

void	my_error(char *str)
{
	printf("ERROR: %s\n", str);
	exit(0);
}

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}
