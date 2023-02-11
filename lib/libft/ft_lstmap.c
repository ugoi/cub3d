/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:18:21 by bogunlan          #+#    #+#             */
/*   Updated: 2022/05/04 02:30:28 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void(*del)(void *))
{
	t_list	*new;
	t_list	*ptr;
	t_list	*head;

	ptr = lst;
	if (!lst)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	head = new;
	while (ptr->next)
	{
		ptr = ptr->next;
		new->next = ft_lstnew(f(ptr->content));
		if (!new->next)
			ft_lstclear(&lst, del);
		new = new->next;
	}
	return (head);
}
