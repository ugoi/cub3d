/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 08:51:05 by sdukic            #+#    #+#             */
/*   Updated: 2022/10/17 08:50:32 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t				i;
	size_t				i2;

	i = 0;
	if (!(*to_find) || to_find == NULL)
		return ((char *) str);
	while ((i < len && str[i]))
	{
		i2 = 0;
		while (to_find[i2] == str[i + i2] && i + i2 < len)
		{
			i2++;
			if (to_find[i2] == '\0')
				return ((char *) str + i);
		}
		i++;
	}
	return (NULL);
}
