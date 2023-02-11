/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:21:18 by sdukic            #+#    #+#             */
/*   Updated: 2022/10/18 21:56:37 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

#define TERMINATOR_LEN 1

static int	ft_str_len(char const *str, char c)
{
	int	fragm_len;

	fragm_len = 0;
	while (str[fragm_len] && *(str + fragm_len) != c)
		fragm_len++;
	return (fragm_len);
}

static int	ft_amount_of_strings(char const *str, char c)
{
	int	i;
	int	amount_of_strings;

	amount_of_strings = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		i = ft_str_len(str, c);
		str += i;
		if (i)
			amount_of_strings++;
	}
	return (amount_of_strings);
}

static char	*ft_cpy(char const *src, int len)
{
	char	*res;

	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = '\0';
	while (len--)
		res[len] = src[len];
	return (res);
}

static char	**ft_free(int str_index, char **res)
{
	while (--str_index >= 0)
		free(res[str_index]);
	free(res);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char			**res;
	int				amount_of_strings;
	int				str_index;
	int				str_len;

	if (!s)
		return (0);
	amount_of_strings = ft_amount_of_strings(s, c);
	res = malloc(sizeof(char *) * (amount_of_strings + TERMINATOR_LEN));
	if (!res)
		return (NULL);
	str_index = 0;
	while (str_index < amount_of_strings)
	{
		while (*s && *s == c)
			s++;
		str_len = ft_str_len(s, c);
		res[str_index] = ft_cpy(s, str_len);
		if (!res[str_index])
			return (ft_free(str_index, res));
		s += str_len;
		str_index++;
	}
	res[amount_of_strings] = 0;
	return (res);
}
