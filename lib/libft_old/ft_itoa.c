/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:45:07 by sdukic            #+#    #+#             */
/*   Updated: 2022/10/18 22:41:23 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include <unistd.h>

static int	ft_numlen(int n)
{
	int	size;

	size = 1;
	if (n < 0)
		size++;
	while (n >= 10 || n <= -10)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static int	ft_amount(int n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		nlen;

	nlen = ft_numlen(n);
	res = malloc(sizeof(char) * nlen + 1);
	if (!res)
		return (NULL);
	res += nlen;
	*res-- = '\0';
	*res-- = ft_amount(n % 10) + '0';
	while (n >= 10 || n <= -10)
	{
		n = n / 10;
		*res-- = ft_amount(n % 10) + '0';
	}
	if (n < 0)
		*res = '-';
	else
		res++;
	return (res);
}
