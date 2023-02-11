/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:19:49 by sdukic            #+#    #+#             */
/*   Updated: 2022/10/15 23:17:28 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memset(void *str, int c, size_t n)
{
	size_t	i;
	char	*str2;

	str2 = str;
	i = 0;
	while (i < n)
	{
		str2[i] = (unsigned char) c;
		i++;
	}
	return (str);
}
