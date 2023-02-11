/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:27:21 by sdukic            #+#    #+#             */
/*   Updated: 2022/10/18 22:55:47 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_skip_first(char const *s1, char const *set)
{
	while (*s1)
	{
		if (ft_strchr(set, *s1) == NULL)
			return ((char *) s1);
		s1++;
	}
	return ((char *) s1);
}

static char	*ft_skip_last(char const *s1, char const *set)
{
	int	set_len;
	int	s1_len;

	set_len = ft_strlen(set);
	s1_len = ft_strlen(s1);
	while (*s1)
		s1++;
	s1--;
	while (s1_len--)
	{
		if (ft_strchr(set, *s1) == NULL)
			return ((char *)(s1));
		s1--;
	}
	return ((char *)(s1));
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*res;
	int			res_len;
	char		*first;
	char		*last;
	char		*res_cast;

	if (!s1)
		return (NULL);
	first = ft_skip_first(s1, set);
	last = ft_skip_last(s1, set);
	res_len = last - first + 1;
	if (res_len < 0)
		res_len = 0;
	res = ft_calloc((res_len + 1), sizeof(char));
	if (!res)
		return (NULL);
	if (!res)
		return (NULL);
	res_cast = res;
	while (first <= last)
		*res_cast++ = *first++;
	return ((char *) res);
}
