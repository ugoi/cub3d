/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 08:37:37 by sdukic            #+#    #+#             */
/*   Updated: 2022/10/18 17:14:15 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char unsigned	*s1_cast;
	const char unsigned	*s2_cast;

	s1_cast = s1;
	s2_cast = s2;
	if (n == 0)
		return (0);
	if (n != 0)
	{
		while (n--)
		{
			if (*s1_cast != *s2_cast)
			{
				return (*s1_cast - *s2_cast);
			}
			s1_cast++;
			s2_cast++;
		}
	}
	return (0);
}
