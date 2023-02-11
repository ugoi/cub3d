/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 08:21:21 by sdukic            #+#    #+#             */
/*   Updated: 2022/10/18 15:59:46 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memchr(const void *str, int c, size_t n)
{
	const unsigned char	*str_cast;

	str_cast = str;
	while (n--)
	{
		if (*str_cast == (unsigned char) c)
			return ((void *) str_cast);
		str_cast++;
	}
	return (NULL);
}
