/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:43:32 by bogunlan          #+#    #+#             */
/*   Updated: 2022/04/23 20:21:10 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	int	lower_case;

	lower_case = c + 32;
	if (lower_case >= 97 && 122 >= lower_case)
		return (lower_case);
	return (c);
}
