/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 17:26:45 by bogunlan          #+#    #+#             */
/*   Updated: 2022/04/24 18:03:28 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			(**ptr)(unsigned int, char);
	unsigned int	i;
	char			*str;

	ptr = &f;
	if (!s || !f)
		return (NULL);
	str = (char *) malloc(sizeof(*str) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = (*ptr)(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
