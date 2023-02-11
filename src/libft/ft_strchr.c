/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:04:05 by bogunlan          #+#    #+#             */
/*   Updated: 2022/05/05 14:27:20 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	const char		*p;

	i = 0;
	p = NULL;
	while (1)
	{
		if (s[i] == (unsigned char) c)
		{
			p = &s[i];
			break ;
		}
		if (s[i] == '\0')
			break ;
		i++;
	}
	return ((char *)(p));
}
