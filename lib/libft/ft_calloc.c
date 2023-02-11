/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:59:16 by bogunlan          #+#    #+#             */
/*   Updated: 2022/05/05 20:03:42 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if ((count > 0) && (size > SIZE_MAX / count))
		return (NULL);
	p = malloc (count * size);
	if (!p)
		return (NULL);
	if (p)
		ft_bzero(p, count * size);
	return (p);
}
