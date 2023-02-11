/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 17:31:21 by bogunlan          #+#    #+#             */
/*   Updated: 2022/04/27 15:01:56 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	unsigned int	len;

	i = 0;
	if ((f != NULL) && (s != NULL))
	{
		len = ft_strlen(s);
		while (i < len)
		{
			(*f)(i, s + i);
			i++;
		}
	}
}
