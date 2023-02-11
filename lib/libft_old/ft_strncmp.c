/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 13:47:30 by sdukic            #+#    #+#             */
/*   Updated: 2022/10/18 20:16:31 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int		i;
	const char unsigned	*s1_cast;
	const char unsigned	*s2_cast;

	s1_cast = (const char unsigned *)s1;
	s2_cast = (const char unsigned *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while ((s1_cast[i] != '\0') && (s2_cast[i] != '\0')
		&& (s1_cast[i] == s2_cast[i]) && i < (n - 1))
		i++;
	return (s1_cast[i] - s2_cast[i]);
}
