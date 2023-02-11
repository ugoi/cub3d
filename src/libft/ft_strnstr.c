/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 20:23:13 by bogunlan          #+#    #+#             */
/*   Updated: 2022/04/30 21:37:58 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *ne, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	unsigned int	temp;

	i = 0;
	if (ne[0] == '\0')
		return ((char *) h);
	while ((i < len) && (h[i] != '\0'))
	{
		k = i;
		j = 0;
		while (ne[j] == h[k]
			&& (j < ft_strlen(ne)) && (k < len) && (ne[j] != '\0'))
		{
			if (j == 0)
				temp = k;
			if (j == ft_strlen(ne) - 1)
				return ((char *) &h[temp]);
			j++;
			k++;
		}
		i++;
	}
	return (NULL);
}
