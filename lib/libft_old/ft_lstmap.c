/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 21:12:21 by sdukic            #+#    #+#             */
/*   Updated: 2022/10/19 02:42:17 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include<stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*res_cast;
	t_list	*prev_lst;

	if (!lst)
		return (NULL);
	res = ft_lstnew(f(lst->content));
	if (!res)
		return (NULL);
	lst = lst->next;
	prev_lst = res;
	while (lst)
	{
		res_cast = ft_lstnew(f(lst->content));
		if (!res_cast)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		prev_lst->next = res_cast;
		prev_lst = res_cast;
		lst = lst->next;
	}
	return (res);
}
