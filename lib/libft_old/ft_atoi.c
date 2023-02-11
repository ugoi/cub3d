/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 22:58:38 by sdukic            #+#    #+#             */
/*   Updated: 2022/10/19 02:54:37 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<limits.h>

int	ft_atoi(const char *str)
{
	int						i;
	unsigned long long int	sign;
	unsigned long long int	num;

	i = 0;
	sign = 1;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	if (num > LONG_MAX)
		return (-(sign == 1));
	return (num * sign);
}
