/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 23:07:19 by sdukic            #+#    #+#             */
/*   Updated: 2022/10/18 21:53:45 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include<stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_lst;

	if (!lst || !del)
		return ;
	if (!*lst)
	{
		free(*lst);
		return ;
	}
	while (*lst)
	{
		next_lst = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = next_lst;
	}
}
