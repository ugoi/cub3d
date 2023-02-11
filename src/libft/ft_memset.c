/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:20:15 by bogunlan          #+#    #+#             */
/*   Updated: 2022/05/05 14:23:55 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len )
{
	unsigned int	i;

	i = 0;
	while (i < len)
	{
		*((char *) b + i) = (unsigned char) c;
		i++;
	}
	return (b);
}
