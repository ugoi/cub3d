/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:17:30 by bogunlan          #+#    #+#             */
/*   Updated: 2022/04/27 16:50:27 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	const char	*p;

	i = ft_strlen(s);
	p = NULL;
	while (i >= 0)
	{
		if (s[i] == (char) c)
		{
			p = &s[i];
			break ;
		}
		i--;
	}
	return ((char *)(p));
}
