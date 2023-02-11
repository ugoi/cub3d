/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:45:19 by sdukic            #+#    #+#             */
/*   Updated: 2022/10/18 21:29:06 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dlen;
	size_t	res;

	if (!dst && !size)
		return (ft_strlen(src));
	dlen = ft_strlen(dst);
	if (dlen < size)
		res = dlen + ft_strlen(src);
	else
		res = ft_strlen(src) + size;
	if (size == 0)
		return (res);
	i = 0;
	if (dlen < size)
	{
		while (src[i] && dlen + i < size - 1)
		{
			dst[dlen + i] = src[i];
			i++;
		}
		dst[dlen + i] = '\0';
	}
	return (res);
}
