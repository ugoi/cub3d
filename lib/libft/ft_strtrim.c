/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:52:26 by bogunlan          #+#    #+#             */
/*   Updated: 2022/04/24 17:51:23 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_b(char const *s1, char const *set)
{
	unsigned int	temp_begin;
	unsigned int	index;
	unsigned char	i;

	i = 0;
	temp_begin = 0;
	while (s1[i] != '\0')
	{
		index = temp_begin;
		if (ft_strchr(set, s1[i++]))
			temp_begin++;
		if (temp_begin == index)
			break ;
	}
	return (temp_begin);
}

static unsigned int	ft_e(char const *s1, char const *set)
{
	unsigned int	temp_end;
	unsigned int	index;
	unsigned char	i;

	i = ft_strlen(s1) - 1;
	temp_end = ft_strlen(s1) - 1;
	while ((i >= 0))
	{
		index = temp_end;
		if (ft_strchr(set, s1[i--]))
			temp_end--;
		if (temp_end == index)
			break ;
	}
	return (temp_end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*str;

	if (!s1)
		return (0);
	str = ft_substr(s1, ft_b(s1, set), ft_e(s1, set) - ft_b(s1, set) + 1);
	if (!str)
		return (NULL);
	return (str);
}
