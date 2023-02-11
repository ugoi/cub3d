/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:29:53 by bogunlan          #+#    #+#             */
/*   Updated: 2022/04/23 20:49:45 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	int	upper_case;

	upper_case = c - 32;
	if (upper_case >= 65 && upper_case <= 90)
		return (upper_case);
	else
		return (c);
}
