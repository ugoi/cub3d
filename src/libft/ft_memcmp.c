/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:59:43 by bogunlan          #+#    #+#             */
/*   Updated: 2022/05/05 13:51:46 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ps1;
	unsigned char	*ps2;
	unsigned int	i;
	unsigned int	val;

	val = 0;
	ps1 = (unsigned char *) s1;
	ps2 = (unsigned char *) s2;
	i = 0;
	if (n == 0)
		return (val);
	while ((i < n - 1) && (ps1[i] == ps2[i]))
		i++;
	val += ps1[i] - ps2[i];
	return (val);
}
