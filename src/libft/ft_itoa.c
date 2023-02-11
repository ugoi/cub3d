/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 20:41:56 by bogunlan          #+#    #+#             */
/*   Updated: 2022/05/05 20:49:19 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sign_checker(int n)
{
	if (n < 0)
		return (-1);
	return (1);
}

static int	num_checker(int n)
{
	long long	nmb;

	nmb = (long long) n;
	if (nmb == -2147483648)
		n = nmb + 1;
	if (n < 0)
		n *= -1;
	return (n);
}

static char	*ft_convert_number(int digit_c, long long nmb, char *res, int tmp_n)
{
	int	i;

	i = 0;
	if (nmb < 0)
		i = 1;
	while (digit_c > 0)
	{
		if ((digit_c == 9) && (nmb == -2147483648))
			res[digit_c + i] = (tmp_n % 10) + 49;
		else
			res[digit_c + i] = (tmp_n % 10) + 48;
		tmp_n /= 10;
		digit_c--;
	}
	return (res);
}

static char	*result(int n, char *res, int sign, int digit_c)
{
	if (sign >= 0)
	{
		res[0] = n + 48;
		res[digit_c + 1] = '\0';
	}
	if (sign < 0)
	{
		res[0] = '-';
		res[1] = n + 48;
		res[digit_c + 2] = '\0';
	}
	return (res);
}

char	*ft_itoa(int n)
{
	int			digit_c;
	int			tmp_n;
	char		*res;
	int			sign;
	long long	nmb;

	digit_c = 0;
	nmb = (long long) n;
	sign = sign_checker(n);
	n = num_checker(n);
	tmp_n = n;
	while (n >= 10 && ++digit_c)
		n /= 10;
	if (sign == 1)
		res = (char *) malloc(sizeof(char) * (digit_c + 2));
	else
		res = (char *) malloc(sizeof(char) * (digit_c + 3));
	if (res == NULL)
		return (NULL);
	if (digit_c > 0)
		ft_convert_number(digit_c, nmb, res, tmp_n);
	res = result(n, res, sign, digit_c);
	return (res);
}
