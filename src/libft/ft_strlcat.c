/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:24:30 by bogunlan          #+#    #+#             */
/*   Updated: 2022/04/29 13:25:41 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	s_len;
	unsigned int	d_len;

	i = 0;
	s_len = ft_strlen(src);
	d_len = ft_strlen(dst);
	if (dstsize == 0)
		return (s_len);
	if (dstsize <= d_len)
		return (s_len + dstsize);
	while (src[i] != '\0' && d_len + i < dstsize - 1)
	{
		dst[d_len + i] = src[i];
		i++;
	}
	dst[d_len + i] = '\0';
	return (d_len + s_len);
}
