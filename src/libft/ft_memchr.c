/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:22:40 by bogunlan          #+#    #+#             */
/*   Updated: 2022/05/05 15:40:14 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	ch;
	unsigned char	*pstr;
	unsigned char	*ret;
	unsigned int	i;

	ch = (unsigned char)c;
	ret = NULL;
	pstr = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (pstr[i] == ch)
		{
			ret = &pstr[i];
			break ;
		}
		i++;
	}
	return (ret);
}
