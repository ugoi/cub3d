/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:23:28 by bogunlan          #+#    #+#             */
/*   Updated: 2022/04/24 04:55:18 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*newstr;
	unsigned int	i;
	unsigned int	j;

	if (!s1 || !s2)
		return (NULL);
	newstr = (char *) malloc(sizeof(*s1) * (ft_strlen(s1)+ ft_strlen(s2) + 1));
	if (!newstr)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
	{
		newstr[i] = s1[i];
	}
	j = -1;
	while (s2[++j] != '\0')
	{
		newstr[i++] = s2[j];
	}
	newstr[i] = '\0';
	return (newstr);
}
